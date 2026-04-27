// Arquivo inicial de lógica de interpretação de texto
#include "TextInterpreter.h"
#include <iostream>
#include <sstream>

TextInterpreter::TextInterpreter(MusicContext& ctx) : context(ctx) {}

void TextInterpreter::loadText(const std::string& input) {
    text = input;
    std::cout << "[TextInterpreter] Texto carregado (tamanho: "
              << text.size() << " chars)\n";
}

void TextInterpreter::clearVoices() {
    voices.clear();
}

const std::vector<Voice>& TextInterpreter::getVoices() const {
    return voices;
}

void TextInterpreter::interpret() {
    clearVoices();

    std::istringstream stream(text);
    std::string line;
    int voiceIndex = 0;

    while (std::getline(stream, line)) {
        Voice voice(voiceIndex);
        voice.processLine(line, context);
        voices.push_back(voice);
        ++voiceIndex;
    }

    std::cout << "[TextInterpreter] Interpretação concluída: "
              << voices.size() << " vozes processadas.\n";
}