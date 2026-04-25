//Arquivo main do Peppertune
#include <iostream>
#include "MusicContext.h"
#include "MusicTranslator.h"
#include "TextInterpreter.h"

int main(){
    
    //Instancia do maestro (120 BPM por padrao)
    TextInterpreter maestro;

    maestro.parseFile("teste.txt");

    std::cout << "BPM Global Final:" << maestro.getGlobalBPM() << std::endl;

    std::vector<MusicContext> vozes = maestro.getVoices();

    for (MusicContext voz : vozes) {
        std::cout << "\n--- Voz " << voz.getVoiceID() << " ---" << std::endl;
        std::cout << "Instrumento: " << voz.getCurrentInstrument() << std::endl;
        std::cout << "Volume: " << voz.getVolume() << std::endl;
    }

    return 0;

}