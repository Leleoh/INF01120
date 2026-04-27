// Interface para vozes
#pragma once

#include <string>
#include <vector>

class MusicContext;

struct VoiceEvent {
    std::string description;
};

class Voice {
private:
    int voiceId;
    std::string rawLine;
    int delayBeats;
    int baseOctave;
    int currentOctave;
    int baseVolume;
    int currentVolume;
    int baseInstrument;
    int currentInstrument;
    char lastNote;
    std::vector<VoiceEvent> generatedEvents;

    void configureDefaultsFromVoiceId();
    std::string parseInitialDelay(const std::string& line);
    void processChar(char c, MusicContext& ctx);

    bool isNoteChar(char c) const;
    bool isPauseChar(char c) const;
    bool isUnmappedVowel(char c) const;

    void handleNote(char c);
    void handlePause(char c);
    void handleInstrumentChange(char c);
    void handleOctaveChange(char c);
    void handleVolumeChange(char c);
    void createInitialSilenceEvents();

public:
    Voice(int id = 0);

    int getVoiceId() const;
    const std::string& getRawLine() const;
    int getDelayBeats() const;
    int getBaseOctave() const;
    int getCurrentOctave() const;
    int getBaseVolume() const;
    int getCurrentVolume() const;
    int getBaseInstrument() const;
    int getCurrentInstrument() const;
    char getLastNote() const;
    const std::vector<VoiceEvent>& getEvents() const;

    void setRawLine(const std::string& line);
    void setDelayBeats(int delay);
    void setBaseOctave(int octave);
    void setCurrentOctave(int octave);
    void setBaseVolume(int volume);
    void setCurrentVolume(int volume);
    void setBaseInstrument(int instrument);
    void setCurrentInstrument(int instrument);
    void setLastNote(char note);

    void addEvent(const std::string& description);
    void clearEvents();

    void processLine(const std::string& line, MusicContext& ctx);
};