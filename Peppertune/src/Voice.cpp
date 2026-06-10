//Arquivo de lógica para as vozes
// Arquivo de lógica para as vozes
#include "Voice.h"
#include "MusicContext.h"

#include <algorithm>
#include <cctype>
#include <iostream>

namespace {
int clampInt(int value, int minValue, int maxValue) {
    return std::max(minValue, std::min(value, maxValue));
}

std::string noteToPitch(char noteChar, int octave) {
    switch (noteChar) {
        case 'A': return "A" + std::to_string(octave);
        case 'B': return "B" + std::to_string(octave);
        case 'C': return "C" + std::to_string(octave);
        case 'D': return "D" + std::to_string(octave);
        case 'E': return "E" + std::to_string(octave);
        case 'F': return "F" + std::to_string(octave);
        case 'G': return "G" + std::to_string(octave);
        case 'H': return "Bb" + std::to_string(octave);
        default:  return "REST";
    }
}
}

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
      baseOctave(5),
      currentOctave(5),
      baseVolume(80),
      currentVolume(80),
      baseInstrument(0),
      currentInstrument(0),
      currentBeat(0),
      lastNote('\0') {
    configureDefaultsFromVoiceId();
}

int Voice::getVoiceId() const { return voiceId; }
const std::string& Voice::getRawLine() const { return rawLine; }
int Voice::getDelayBeats() const { return delayBeats; }
int Voice::getBaseOctave() const { return baseOctave; }
int Voice::getCurrentOctave() const { return currentOctave; }
int Voice::getBaseVolume() const { return baseVolume; }
int Voice::getCurrentVolume() const { return currentVolume; }
int Voice::getBaseInstrument() const { return baseInstrument; }
int Voice::getCurrentInstrument() const { return currentInstrument; }
int Voice::getCurrentBeat() const { return currentBeat; }
char Voice::getLastNote() const { return lastNote; }
const std::vector<VoiceEvent>& Voice::getEvents() const { return generatedEvents; }

void Voice::setRawLine(const std::string& line) { rawLine = line; }
void Voice::setDelayBeats(int delay) { delayBeats = (delay >= 0) ? delay : 0; }
void Voice::setBaseOctave(int octave) { baseOctave = clampInt(octave, 0, 9); }
void Voice::setCurrentOctave(int octave) { currentOctave = clampInt(octave, 0, 9); }
void Voice::setBaseVolume(int volume) { baseVolume = clampInt(volume, 0, 127); }
void Voice::setCurrentVolume(int volume) { currentVolume = clampInt(volume, 0, 127); }
void Voice::setBaseInstrument(int instrument) { baseInstrument = clampInt(instrument, 0, 127); }
void Voice::setCurrentInstrument(int instrument) { currentInstrument = clampInt(instrument, 0, 127); }
void Voice::setCurrentBeat(int beat) { currentBeat = (beat >= 0) ? beat : 0; }
void Voice::setLastNote(char note) { lastNote = note; }

void Voice::addEvent(const VoiceEvent& event) {
    generatedEvents.push_back(event);
}

void Voice::clearEvents() {
    generatedEvents.clear();
}

void Voice::configureDefaultsFromVoiceId() {
    static const int octaveCycle[] = {6, 5, 4, 3};
    static const int volumeCycle[] = {100, 80, 60, 40};
    static const int instrumentCycle[] = {6, 20, 0, 70};

    const int index = ((voiceId % 4) + 4) % 4;

    setBaseOctave(octaveCycle[index]);
    setCurrentOctave(baseOctave);

    setBaseVolume(volumeCycle[index]);
    setCurrentVolume(baseVolume);

    setBaseInstrument(instrumentCycle[index]);
    setCurrentInstrument(baseInstrument);

    setCurrentBeat(0);
    delayBeats = 0;
    lastNote = '\0';
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

bool Voice::isNoteChar(char c) const {
    return c >= 'A' && c <= 'H';
}

bool Voice::isPauseChar(char c) const {
    return c >= 'a' && c <= 'h';
}

bool Voice::isUnmappedVowel(char c) const {
    return c == 'O' || c == 'o' ||
           c == 'I' || c == 'i' ||
           c == 'U' || c == 'u';
}

void Voice::handleNote(char c) {
    setLastNote(c);

    addEvent({
        VoiceEventType::Note,
        voiceId,
        currentBeat,
        c,
        noteToPitch(c, currentOctave),
        1,
        currentVolume,
        currentInstrument,
        -1,
        currentOctave
    });

    ++currentBeat;
}

void Voice::handlePause(char c) {
    addEvent({
        VoiceEventType::Rest,
        voiceId,
        currentBeat,
        c,
        "",
        1,
        currentVolume,
        currentInstrument,
        -1,
        currentOctave
    });

    ++currentBeat;
}

void Voice::handleInstrumentChange(char c) {
    if (c == '!') {
        setCurrentInstrument(22);
    } else if (c == ';') {
        setCurrentInstrument(15);
    } else if (c == ',') {
        setCurrentInstrument(20);
    } else if (isUnmappedVowel(c)) {
        setCurrentInstrument(110);
    }

    addEvent({
        VoiceEventType::InstrumentChange,
        voiceId,
        currentBeat,
        c,
        "",
        0,
        currentVolume,
        currentInstrument,
        -1,
        currentOctave
    });
}

void Voice::handleOctaveChange(char c) {
    if (c == '?' || c == '.') {
        if (currentOctave < 9) {
            setCurrentOctave(currentOctave + 1);
        } else {
            setCurrentOctave(baseOctave);
        }
    } else if (c == 'V') {
        setCurrentOctave(currentOctave - 1);
    }

    addEvent({
        VoiceEventType::OctaveChange,
        voiceId,
        currentBeat,
        c,
        "",
        0,
        currentVolume,
        currentInstrument,
        -1,
        currentOctave
    });
}

void Voice::handleVolumeChange(char c) {
    if (c == ' ') {
        setCurrentVolume(std::min(currentVolume * 2, 127));

        addEvent({
            VoiceEventType::VolumeChange,
            voiceId,
            currentBeat,
            c,
            "",
            0,
            currentVolume,
            currentInstrument,
            -1,
            currentOctave
        });
    }
}

void Voice::handleBpmChange(MusicContext& ctx, int delta) {
    if (delta > 0) {
        ctx.increaseBpm(delta);
    } else {
        ctx.decreaseBpm(-delta);
    }

    addEvent({
        VoiceEventType::BpmChange,
        voiceId,
        currentBeat,
        '\0',
        "",
        0,
        currentVolume,
        currentInstrument,
        ctx.getBpm(),
        currentOctave
    });
}

void Voice::handleRepeatOrPause(char c) {
    if (lastNote != '\0') {
        addEvent({
            VoiceEventType::RepeatLastNote,
            voiceId,
            currentBeat,
            c,
            noteToPitch(lastNote, currentOctave),
            1,
            currentVolume,
            currentInstrument,
            -1,
            currentOctave
        });
    } else {
        addEvent({
            VoiceEventType::Rest,
            voiceId,
            currentBeat,
            c,
            "",
            1,
            currentVolume,
            currentInstrument,
            -1,
            currentOctave
        });
    }

    ++currentBeat;
}

void Voice::createInitialSilenceEvents() {
    for (int i = 0; i < delayBeats; ++i) {
        addEvent({
            VoiceEventType::Rest,
            voiceId,
            currentBeat,
            '\0',
            "",
            1,
            currentVolume,
            currentInstrument,
            -1,
            currentOctave
        });

        ++currentBeat;
    }
}

void Voice::processChar(char c, MusicContext& ctx) {
    if (isNoteChar(c)) {
        handleNote(c);
        return;
    }

    if (isPauseChar(c)) {
        handlePause(c);
        return;
    }

    if (c == '!' || c == ';' || c == ',' || isUnmappedVowel(c)) {
        handleInstrumentChange(c);
        return;
    }

    if (c == '?' || c == 'V' || c == '.') {
        handleOctaveChange(c);
        return;
    }

    if (c == ' ') {
        handleVolumeChange(c);
        return;
    }

    if (c == '>') {
        handleBpmChange(ctx, 10);
        return;
    }

    if (c == '<') {
        handleBpmChange(ctx, -10);
        return;
    }

    if (!std::isspace(static_cast<unsigned char>(c))) {
        handleRepeatOrPause(c);
    }
}

void Voice::processLine(const std::string& line, MusicContext& ctx) {
    setRawLine(line);
    clearEvents();
    configureDefaultsFromVoiceId();

    // Emite os eventos de configuração inicial para que o arquivo MIDI grave o instrumento e volume padrão, e não apenas o Piano.
    addEvent({VoiceEventType::InstrumentChange, voiceId, 0, '\0', "", 0, currentVolume, currentInstrument, -1, currentOctave});
    addEvent({VoiceEventType::VolumeChange, voiceId, 0, '\0', "", 0, currentVolume, currentInstrument, -1, currentOctave});

    std::string content = parseInitialDelay(line);
    createInitialSilenceEvents();

    for (char c : content) {
        processChar(c, ctx);
    }

    std::cout << "[Voice " << voiceId << "] Processando linha: " << rawLine
              << " | delay=" << delayBeats
              << " | eventos=" << generatedEvents.size()
              << " | baseOctave=" << baseOctave
              << " | baseVolume=" << baseVolume
              << " | baseInstrument=" << baseInstrument
              << " | currentInstrument=" << currentInstrument
              << " | beatFinal=" << currentBeat
              << " | BPM global=" << ctx.getBpm()
              << std::endl;
}