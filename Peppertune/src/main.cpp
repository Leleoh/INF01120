#include <iostream>
#include "MusicContext.h"
#include "TextInterpreter.h"
#include "MidiGenerator.h"

int main() {
    std::cout << "=== Peppertune - Fase 2 ate o passo 7 ===\n\n";

    MusicContext contexto;
    TextInterpreter interpreter(contexto);
    MidiGenerator midiGenerator;

    const std::string input =
        "[0] C D E F ,\n"
        "[4] > G A H C !\n"
        "[2] ? A B C ;\n"
        "[1] V G F E ,";

    interpreter.loadText(input);
    interpreter.interpret();

    const auto& voices = interpreter.getVoices();

    for (const auto& voice : voices) {
        std::cout << "\nEventos da voz " << voice.getVoiceId() << ":\n";
        for (const auto& event : voice.getEvents()) {
            std::cout << "- " << event.description << '\n';
        }
    }

    midiGenerator.generateAndPlay(voices);

    std::cout << "\nBPM global final: " << contexto.getBpm() << std::endl;
    return 0;
}