#ifndef MUSICTRANSLATOR_H
#define MUSICTRANSLATOR_H
#include "MusicContext.h"

class MusicTranslator{
    public:

    //Função para tratar o mapeamento de letras para som
    //Parâmetros são sobre as letras, ritmo e voz
    static void applyMapping(char letter, MusicContext& currentVoice, int& globalBPM);

};

#endif