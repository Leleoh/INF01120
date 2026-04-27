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
char Voice::getLastNote() const { return lastNote; }
const std::vector<VoiceEvent>& Voice::getEvents() const { return generatedEvents; }

void Voice::setRawLine(const std::string& line) { rawLine = line; }
void Voice::setDelayBeats(int delay) { delayBeats = (delay >= 0) ? delay : 0; }
void Voice::setBaseOctave(int octave) {
    baseOctave = clampInt(octave, 0, 9);
}
void Voice::setCurrentOctave(int octave) {
    currentOctave = clampInt(octave, 0, 9);
}
void Voice::setBaseVolume(int volume) {
    baseVolume = clampInt(volume, 0, 127);
}
void Voice::setCurrentVolume(int volume) {
    currentVolume = clampInt(volume, 0, 127);
}
void Voice::setBaseInstrument(int instrument) {
    baseInstrument = clampInt(instrument, 0, 127);
}
void Voice::setCurrentInstrument(int instrument) {
    currentInstrument = clampInt(instrument, 0, 127);
}
void Voice::setLastNote(char note) { lastNote = note; }

void Voice::addEvent(const std::string& description) {
    generatedEvents.push_back({description});
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

    addEvent(
        "NOTE voice=" + std::to_string(voiceId) +
        " note=" + std::string(1, c) +
        " octave=" + std::to_string(currentOctave) +
        " volume=" + std::to_string(currentVolume) +
        " instrument=" + std::to_string(currentInstrument)
    );
}

void Voice::handlePause(char c) {
    addEvent(
        "PAUSE voice=" + std::to_string(voiceId) +
        " symbol=" + std::string(1, c)
    );
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

    addEvent(
        "INSTRUMENT_CHANGE voice=" + std::to_string(voiceId) +
        " instrument=" + std::to_string(currentInstrument)
    );
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

    addEvent(
        "OCTAVE_CHANGE voice=" + std::to_string(voiceId) +
        " octave=" + std::to_string(currentOctave)
    );
}

void Voice::handleVolumeChange(char c) {
    if (c == ' ') {
        setCurrentVolume(std::min(currentVolume * 2, 127));

        addEvent(
            "VOLUME_CHANGE voice=" + std::to_string(voiceId) +
            " volume=" + std::to_string(currentVolume)
        );
    }
}

void Voice::createInitialSilenceEvents() {
    for (int i = 0; i < delayBeats; ++i) {
        addEvent(
            "INITIAL_DELAY voice=" + std::to_string(voiceId) +
            " beat=" + std::to_string(i + 1)
        );
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
        ctx.increaseBpm();
        addEvent(
            "BPM_CHANGE voice=" + std::to_string(voiceId) +
            " bpm=" + std::to_string(ctx.getBpm())
        );
        return;
    }

    if (c == '<') {
        ctx.decreaseBpm();
        addEvent(
            "BPM_CHANGE voice=" + std::to_string(voiceId) +
            " bpm=" + std::to_string(ctx.getBpm())
        );
        return;
    }

    if (!std::isspace(static_cast<unsigned char>(c))) {
        if (lastNote != '\0') {
            addEvent(
                "REPEAT_LAST_NOTE voice=" + std::to_string(voiceId) +
                " note=" + std::string(1, lastNote) +
                " octave=" + std::to_string(currentOctave) +
                " volume=" + std::to_string(currentVolume) +
                " instrument=" + std::to_string(currentInstrument)
            );
        } else {
            addEvent(
                "PAUSE voice=" + std::to_string(voiceId) +
                " symbol=" + std::string(1, c)
            );
        }
    }
}

void Voice::processLine(const std::string& line, MusicContext& ctx) {
    setRawLine(line);
    clearEvents();
    configureDefaultsFromVoiceId();

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
              << " | BPM global=" << ctx.getBpm()
              << std::endl;
}