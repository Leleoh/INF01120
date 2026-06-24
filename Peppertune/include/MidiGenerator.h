//Interface MIDI
// Interface MIDI
#pragma once

#include <string>
#include <vector>
#include <atomic>
#include "Voice.h"

class MidiGenerator {
public:
    void generateAndPlay(const std::vector<std::vector<VoiceEvent>>& voiceEvents, std::atomic<bool>* isPaused = nullptr);
    void saveToFile(const std::vector<std::vector<VoiceEvent>>& voiceEvents,
                    const std::string& filename = "peppertune_fuga.mid");
};