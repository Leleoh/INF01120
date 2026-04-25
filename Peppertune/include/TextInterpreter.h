//Arquivo de interface do TextInterpreter
#ifndef TEXTINTERPRETER_H
#define TEXTINTERPRETER_H

#include <string>
#include <vector>
#include "MusicContext.h"

class TextInterpreter{
    private:

    int globalBPM;

    //Array dinâmico que guarda as vozes (linhas)
    std::vector<MusicContext> voices;

    public:
    TextInterpreter();

    //Função principal que abre o arquivo e lê o texto
    void parseFile(const std::string& filepath);

    //Getters para gerar áudio
    int getGlobalBPM() const;
    std::vector<MusicContext> getVoices() const;

};

#endif