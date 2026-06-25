//Arquivo de lógica para as vozes
// Arquivo de lógica para as vozes
#include "Voice.h"
#include "MusicContext.h"
#include "MusicTranslator.h"

#include <algorithm>
#include <cctype>
#include <iostream>

std::string VoiceEvent::toString() const {
    std::string typeName;

    switch (type) {
        case VoiceEventType::Note: typeName = "NOTE"; break;
        case VoiceEventType::Rest: typeName = "REST"; break;
        case VoiceEventType::InstrumentChange: typeName = "INSTRUMENT_CHANGE"; break;
        case VoiceEventType::BpmChange: typeName = "BPM_CHANGE"; break;
        case VoiceEventType::OctaveChange: typeName = "OCTAVE_CHANGE"; break;
        case VoiceEventType::VolumeChange: typeName = "VOLUME_CHANGE"; break;
        case VoiceEventType::RepeatLastNote: typeName = "REPEAT_LAST_NOTE"; break;
    }

    std::string result =
        typeName +
        " voice=" + std::to_string(voiceId) +
        " beat=" + std::to_string(beat);

    if (!pitch.empty()) {
        result += " pitch=" + pitch;
    }

    if (duration > 0) {
        result += " duration=" + std::to_string(duration);
    }

    if (volume >= 0) {
        result += " volume=" + std::to_string(volume);
    }

    if (instrument >= 0) {
        result += " instrument=" + std::to_string(instrument);
    }

    if (bpm >= 0) {
        result += " bpm=" + std::to_string(bpm);
    }

    if (octave >= 0) {
        result += " octave=" + std::to_string(octave);
    }

    if (symbol != '\0') {
        result += " symbol=" + std::string(1, symbol);
    }

    return result;
}

Voice::Voice(int id)
    : voiceId(id),
      rawLine(""),
      delayBeats(0),
      currentBeat(0),
      lastNote('\0') {
    
}

int Voice::getVoiceId() const { return voiceId; }
const std::string& Voice::getRawLine() const { return rawLine; }
int Voice::getDelayBeats() const { return delayBeats; }
int Voice::getCurrentBeat() const { return currentBeat; }
char Voice::getLastNote() const { return lastNote; }
const std::vector<VoiceEvent>& Voice::getEvents() const { return generatedEvents; }

void Voice::setRawLine(const std::string& line) { rawLine = line; }
void Voice::setDelayBeats(int delay) { delayBeats = (delay >= 0) ? delay : 0; }
void Voice::setCurrentBeat(int beat) { currentBeat = (beat >= 0) ? beat : 0; }
void Voice::setLastNote(char note) { lastNote = note; }

void Voice::addEvent(const VoiceEvent& event) {
    generatedEvents.push_back(event);
}

void Voice::clearEvents() {
    generatedEvents.clear();
}



std::string Voice::parseInitialDelay(const std::string& line) {
    delayBeats = 0;

    if (line.size() < 3 || line.front() != '[') {
        return line;
    }

    std::size_t closingBracket = line.find(']');
    if (closingBracket == std::string::npos || closingBracket == 1) {
        return line;
    }

    for (std::size_t i = 1; i < closingBracket; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(line[i]))) {
            return line;
        }
    }

    setDelayBeats(std::stoi(line.substr(1, closingBracket - 1)));

    std::size_t contentStart = closingBracket + 1;
    while (contentStart < line.size() &&
           std::isspace(static_cast<unsigned char>(line[contentStart]))) {
        ++contentStart;
    }

    return line.substr(contentStart);
}



void Voice::createInitialSilenceEvents(MusicContext& ctx) {
    for (int i = 0; i < delayBeats; ++i) {
        addEvent({
            VoiceEventType::Rest,
            voiceId,
            currentBeat,
            '\0',
            "",
            1,
            ctx.getVolume(),
            ctx.getCurrentInstrument(),
            -1,
            ctx.getCurrentOctave()
        });

        ++currentBeat;
    }
}

void Voice::processLine(const std::string& line, MusicContext& ctx) {
    setRawLine(line);
    clearEvents();

    // Emite os eventos de configuração inicial
    addEvent({VoiceEventType::InstrumentChange, voiceId, 0, '\0', "", 0, ctx.getVolume(), ctx.getCurrentInstrument(), -1, ctx.getCurrentOctave()});
    addEvent({VoiceEventType::VolumeChange, voiceId, 0, '\0', "", 0, ctx.getVolume(), ctx.getCurrentInstrument(), -1, ctx.getCurrentOctave()});
    addEvent({VoiceEventType::BpmChange, voiceId, 0, '\0', "", 0, ctx.getVolume(), ctx.getCurrentInstrument(), ctx.getBpm(), ctx.getCurrentOctave()});

    std::string content = parseInitialDelay(line);
    createInitialSilenceEvents(ctx);

    for (char c : content) {
        MusicTranslator::translateChar(c, *this, ctx);
    }

    std::cout << "[Voice " << voiceId << "] Processando linha: " << rawLine
              << " | delay=" << delayBeats
              << " | eventos=" << generatedEvents.size()
              << " | BPM global=" << ctx.getBpm()
              << std::endl;
}