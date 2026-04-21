//Arquivo inicial de lógica de interpretação de texto

#include "TextInterpreter.h"
#include <iostream>
#include <fstream>

TextInterpreter::TextInterpreter(MusicContext& ctx) : context(ctx) {}

void TextInterpreter::loadText(const std::string& input) {
    text = input;
    std::cout << "[TextInterpreter] Texto carregado (tamanho: " << text.size() << " chars)\n";
}

void TextInterpreter::interpret() {
    std::cout << "[TextInterpreter] Interpretando... (lógica de fuga será implementada no Passo 2)\n";
}