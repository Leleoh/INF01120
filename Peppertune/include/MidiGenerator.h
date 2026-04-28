// Interface MIDI
#pragma once

#include <string>
#include <vector>
#include "Voice.h"

class MidiGenerator {
public:
    void generateAndPlay(const std::vector<std::vector<VoiceEvent>>& voiceEvents);
    void saveToFile(const std::vector<std::vector<VoiceEvent>>& voiceEvents,
                    const std::string& filename = "peppertune_fuga.mid");
};