// Arquivo de lógica MIDI
#include "MidiGenerator.h"
#include <iostream>

void MidiGenerator::generateAndPlay(const std::vector<Voice>& voices) {
    std::cout << "[MidiGenerator] Gerando eventos para " << voices.size()
              << " vozes.\n";

    for (const auto& voice : voices) {
        std::cout << "[MidiGenerator] Voice " << voice.getVoiceId()
                  << " | eventos=" << voice.getEvents().size()
                  << " | delay=" << voice.getDelayBeats()
                  << '\n';
    }
}

void MidiGenerator::saveToFile(const std::string& filename) {
    std::cout << "[MidiGenerator] MIDI salvo em: " << filename << std::endl;
}