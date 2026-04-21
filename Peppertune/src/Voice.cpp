//Arquivo de lógica para as vozes

#include "Voice.h"
#include <iostream>

Voice::Voice(int id) : voiceId(id) {}

int Voice::getVoiceId() const {
    return voiceId;
}

void Voice::processLine(const std::string& line, MusicContext& ctx) {
    //Stub - implentação vem no passo 2
    std::cout << "[Voice " << voiceId << "] Processando linha: " << line << std::endl;
}