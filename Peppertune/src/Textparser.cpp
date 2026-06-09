#include "TextParser.h"


#include <iostream>
#include <string>
#include <sstream>

// Implementação do construtor para inicializar o vetor de vozes
TextParser::TextParser() :voices(Peppertune::Constants::MAX_VOICES) {
}
//parser que separa o texto recebido da interface em linhas (vozes) e as armazena no vetor de vozes.
void TextParser::Parse(const char* text) {
    std::stringstream input(text);
    std::string token;
    size_t start = 0;
    int voiceIndex = 0;

    while (std::getline(input, token, '\n')) {
        if (voiceIndex >= Peppertune::Constants::MAX_VOICES) {
            printf("numeromaximo de vozes atingido");
            break;
        }
        voices[voiceIndex++] = token;
}

}

//get de voz a partir do índice, para ser usado pelo TextInterpreter.
std::string TextParser::GetVoice(int index) {
        if (index >= 0 && index < voices.size()) {
        return voices[index];
      } else {
        throw std::out_of_range("Index out of range.");
    }
}