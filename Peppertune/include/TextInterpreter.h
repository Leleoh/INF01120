//Arquivo de interface do TextInterpreter
#ifndef TEXTINTERPRETER_H
#define TEXTINTERPRETER_H

#include <string>
#include <vector>
#include "MusicContext.h"
#include "Voice.h"

class TextInterpreter{
    private:

    int globalBPM;

    //Array dinâmico que guarda as vozes (linhas)
    std::vector<MusicContext> voices;
    
    //Armazena os eventos processados pela lógica do MidiGenerator
    std::vector<std::vector<VoiceEvent>> allVoiceEvents;

    public:
    TextInterpreter();

    //Função principal que abre o arquivo e lê o texto
    void parseFile(const std::string& filepath);

    //Getters para gerar áudio
    int getGlobalBPM() const;
    std::vector<MusicContext> getVoices() const;
    std::vector<std::vector<VoiceEvent>> getAllVoiceEvents() const;

};

#endif