//Arquivo main do Peppertune

#include <iostream>
#include "MusicContext.h"

int main() {
    std::cout << "=== Peppertune - Fase 2 (Passo 1 - Correções concluídas) ===\n\n";

    MusicContext contexto;

    std::cout << "Volume inicial: " << contexto.getVolume() << std::endl;
    contexto.doubleVolume();
    std::cout << "Volume após dobrar: " << contexto.getVolume() << std::endl;

    std::cout << "Oitava atual: " << contexto.getCurrentOctave() << std::endl;
    contexto.raiseOctave();
    std::cout << "Oitava após raiseOctave(): " << contexto.getCurrentOctave() << std::endl;

    contexto.setInstrument(22); // Harmonica (general MIDI)
    std::cout << "Instrumento atual: " << contexto.getCurrentInstrument() << " (Harmonica)\n";

    std::cout << "\n✅ Todas as classes do passo 1 tão compilando!\n";
    std::cout << "Rode o build e testa de novo.\n";

    return 0;
}