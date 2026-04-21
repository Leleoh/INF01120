//Interface MIDI

#pragma once
#include <string>
#include <vector>
#include "Voice.h"

class MidiGenerator {
public:
    void generateAndPlay(const std::vector<Voice>& voices);
    void saveToFile(const std::string& filename = "peppertune_fuga.mid");
};