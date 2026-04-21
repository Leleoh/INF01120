//Arquivo de lógica MIDI

#include "MidiGenerator.h"
#include <iostream>

void MidiGenerator::generateAndPlay(const std::vector<Voice>& voices) {
    std::cout << "[MidiGenerator] Gerando MIDI para " << voices.size() << " vozes (implementação completa no Passo 2)\n";
}

void MidiGenerator::saveToFile(const std::string& filename) {
    std::cout << "[MidiGenerator] MIDI salvo em: " << filename << std::endl;
}