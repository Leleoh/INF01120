//Interface para vozes
// Interface para vozes
#pragma once

#include <string>
#include <vector>

class MusicContext;

enum class VoiceEventType {
    Note,
    Rest,
    InstrumentChange,
    BpmChange,
    OctaveChange,
    VolumeChange,
    RepeatLastNote
};

struct VoiceEvent {
    VoiceEventType type;
    int voiceId;
    int beat;
    char symbol;
    std::string pitch;
    int duration;
    int volume;
    int instrument;
    int bpm;
    int octave;

    std::string toString() const;
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
    int currentBeat;
    char lastNote;
    std::vector<VoiceEvent> generatedEvents;

    void configureDefaultsFromVoiceId();
public:
    void addEvent(const VoiceEvent& event);
    std::string parseInitialDelay(const std::string& line);
    void createInitialSilenceEvents();

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
    int getCurrentBeat() const;
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
    void setCurrentBeat(int beat);
    void setLastNote(char note);

    void clearEvents();
    void processLine(const std::string& line, MusicContext& ctx);
};