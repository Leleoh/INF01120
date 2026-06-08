//Arquivo de logica MIDI
#include "MidiGenerator.h"
#include <iostream>
#include <map>
#include <string>

//#include "MidiFile.h"

#define TSF_IMPLEMENTATION
#include "tsf.h"

#define TML_IMPLEMENTATION
#include "tml.h"

#include <SDL3/SDL.h>

static int getMidiNote(const std::string& pitch) {
    if (pitch == "REST" || pitch.empty()) return 0;
    
    std::string noteStr = pitch.substr(0, pitch.length() - 1);
    int octave = pitch.back() - '0';
    
    int noteOffset = 0;
    if (noteStr == "C") noteOffset = 0;
    else if (noteStr == "C#") noteOffset = 1;
    else if (noteStr == "D") noteOffset = 2;
    else if (noteStr == "D#") noteOffset = 3;
    else if (noteStr == "E") noteOffset = 4;
    else if (noteStr == "F") noteOffset = 5;
    else if (noteStr == "F#") noteOffset = 6;
    else if (noteStr == "G") noteOffset = 7;
    else if (noteStr == "G#") noteOffset = 8;
    else if (noteStr == "A") noteOffset = 9;
    else if (noteStr == "Bb") noteOffset = 10;
    else if (noteStr == "B") noteOffset = 11;
    
    // MIDI Note 60 is Middle C (C4)
    // C0 is 12. So (octave + 1) * 12 + offset
    return (octave + 1) * 12 + noteOffset;
}

void MidiGenerator::saveToFile(const std::vector<std::vector<VoiceEvent>>& voiceEvents,
                               const std::string& filename) {
    if (voiceEvents.empty()) {
        std::cout << "[MidiGenerator] Nenhuma voz recebida. Abortando salvamento.\n";
        return;
    }

    std::cout << "[MidiGenerator] Salvando " << voiceEvents.size() << " vozes no arquivo: " << filename << '\n';

    smf::MidiFile midifile;
    int tpq = 120; // Ticks per quarter note
    midifile.setTicksPerQuarterNote(tpq);

    int track = 0;
    for (const auto& voice : voiceEvents) {
        // Se a voz não tem eventos, ignoramos para não criar uma track vazia (o que causa o crash)
        if (voice.empty()) continue;

        // O MidiFile já vem com 1 track por padrão. Se precisarmos de mais, adicionamos.
        while (midifile.getTrackCount() <= track) {
            midifile.addTrack();
        }

        int currentTick = 0;
        int channel = track % 16;
        if (channel == 9) channel = 10; // Evita o canal 9 (10 na base 1) que eh percussao

        for (const auto& ev : voice) {
            int eventDurationTicks = ev.duration * tpq;
            
            if (ev.type == VoiceEventType::InstrumentChange) {
                midifile.addPatchChange(track, currentTick, channel, ev.instrument);
            }
            else if (ev.type == VoiceEventType::VolumeChange) {
                midifile.addController(track, currentTick, channel, 7, ev.volume);
            }
            else if (ev.type == VoiceEventType::BpmChange) {
                midifile.addTempo(track, currentTick, ev.bpm);
            }
            else if (ev.type == VoiceEventType::Note || ev.type == VoiceEventType::RepeatLastNote) {
                if (ev.pitch != "REST" && !ev.pitch.empty()) {
                    int midiNote = getMidiNote(ev.pitch);
                    midifile.addNoteOn(track, currentTick, channel, midiNote, ev.volume);
                    midifile.addNoteOff(track, currentTick + eventDurationTicks, channel, midiNote);
                }
                currentTick += eventDurationTicks;
            }
            else if (ev.type == VoiceEventType::Rest) {
                currentTick += eventDurationTicks;
            }
        }
        track++;
    }

    midifile.sortTracks();
    midifile.write(filename);
    std::cout << "[MidiGenerator] Arquivo MIDI gerado com sucesso: " << filename << '\n';
}

void MidiGenerator::generateAndPlay(const std::vector<std::vector<VoiceEvent>>& voiceEvents) {
    if (voiceEvents.empty()) {
        std::cout << "[MidiGenerator] Nenhuma voz recebida. Abortando audio.\n";
        return;
    }

    std::cout << "[MidiGenerator] Preparando audio...\n";
    
    // 1. Gera o arquivo temporario
    std::string tempFilename = "temp_play.mid";
    saveToFile(voiceEvents, tempFilename);

    // 2. Carrega o SoundFont (Sintetizador)
    tsf* f = tsf_load_filename("TimGM6mb.sf2");
    if (!f) {
        std::cerr << "Erro: Arquivo TimGM6mb.sf2 nao encontrado!\n";
        return;
    }

    // 3. Carrega o arquivo MIDI com o TinyMidiLoader
    tml_message* midi = tml_load_filename(tempFilename.c_str());
    tml_message* midi_head = midi;
    if (!midi) {
        std::cerr << "Erro ao carregar o arquivo temporario MIDI.\n";
        tsf_close(f);
        return;
    }

    // 4. Inicializa o Audio SDL3
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        std::cerr << "Falha SDL_Audio: " << SDL_GetError() << "\n";
        tml_free(midi_head);
        tsf_close(f);
        return;
    }

    SDL_AudioSpec spec;
    spec.freq = 44100;
    spec.format = SDL_AUDIO_F32;
    spec.channels = 2;

    SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
    if (!stream) {
        std::cerr << "Falha stream SDL3: " << SDL_GetError() << "\n";
        tml_free(midi_head);
        tsf_close(f);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return;
    }

    tsf_set_output(f, TSF_STEREO_INTERLEAVED, spec.freq, 0.0f);
    SDL_ResumeAudioStreamDevice(stream);

    std::cout << "[MidiGenerator] Tocando! Espere a musica terminar...\n";

    int RenderSampleBlock = 512;
    float* sampleBuffer = new float[RenderSampleBlock * 2];
    
    double msec = 0;
    int tailFrames = spec.freq * 2; // 2 segundos de release

    while (true) {
        if (SDL_GetAudioStreamAvailable(stream) < (int)(spec.freq * sizeof(float) * 2 / 2)) {
            // Processa as mensagens MIDI do tempo atual
            while (midi && midi->time <= msec) {
                switch (midi->type) {
                    case TML_PROGRAM_CHANGE:
                        tsf_channel_set_presetnumber(f, midi->channel, midi->program, (midi->channel == 9));
                        break;
                    case TML_NOTE_ON:
                        tsf_channel_note_on(f, midi->channel, midi->key, midi->velocity / 127.0f);
                        break;
                    case TML_NOTE_OFF:
                        tsf_channel_note_off(f, midi->channel, midi->key);
                        break;
                    case TML_PITCH_BEND:
                        tsf_channel_set_pitchwheel(f, midi->channel, midi->pitch_bend);
                        break;
                    case TML_CONTROL_CHANGE:
                        tsf_channel_midi_control(f, midi->channel, midi->control, midi->control_value);
                        break;
                }
                midi = midi->next;
            }

            if (!midi) {
                if (tailFrames <= 0) break;
                tailFrames -= RenderSampleBlock;
            }

            // Sintetiza o audio e joga na stream do SDL3
            tsf_render_float(f, sampleBuffer, RenderSampleBlock, 0);
            SDL_PutAudioStreamData(stream, sampleBuffer, RenderSampleBlock * sizeof(float) * 2);

            msec += (RenderSampleBlock * 1000.0) / spec.freq;
        } else {
            SDL_Delay(5);
        }
    }

    std::cout << "[MidiGenerator] Fim da reproducao.\n";

    delete[] sampleBuffer;
    SDL_DestroyAudioStream(stream);
    tsf_close(f);
    tml_free(midi_head);
}