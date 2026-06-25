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
    int currentBeat;
    char lastNote;
    std::vector<VoiceEvent> generatedEvents;

public:
    void addEvent(const VoiceEvent& event);
    std::string parseInitialDelay(const std::string& line);
    void createInitialSilenceEvents(MusicContext& ctx);

    Voice(int id = 0);

    int getVoiceId() const;
    const std::string& getRawLine() const;
    int getDelayBeats() const;
    int getCurrentBeat() const;
    char getLastNote() const;
    const std::vector<VoiceEvent>& getEvents() const;

    void setRawLine(const std::string& line);
    void setDelayBeats(int delay);
    void setCurrentBeat(int beat);
    void setLastNote(char note);

    void clearEvents();
    void processLine(const std::string& line, MusicContext& ctx);
};