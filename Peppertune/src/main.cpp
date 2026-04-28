#include <iostream>
#include <string>
#include "MusicContext.h"
#include "TextInterpreter.h"
#include "MidiGenerator.h"

static void printSeparator() {
    std::cout << "--------------------------------------------------\n";
}

static void printEventList(const std::vector<VoiceEvent>& events) {
    for (const auto& event : events) {
        std::cout << "    - " << event.toString() << '\n';
    }
}

static void printVoiceSummary(const Voice& voice) {
    printSeparator();
    std::cout << "Voz " << voice.getVoiceId() << '\n';
    printSeparator();

    std::cout << "  Linha original        : " << voice.getRawLine() << '\n';
    std::cout << "  Delay                 : " << voice.getDelayBeats() << " beats\n";
    std::cout << "  Oitava base           : " << voice.getBaseOctave() << '\n';
    std::cout << "  Volume base           : " << voice.getBaseVolume() << '\n';
    std::cout << "  Instrumento base      : " << voice.getBaseInstrument() << '\n';
    std::cout << "  Instrumento atual     : " << voice.getCurrentInstrument() << '\n';
    std::cout << "  Beat final            : " << voice.getCurrentBeat() << '\n';
    std::cout << "  Quantidade de eventos : " << voice.getEvents().size() << '\n';
    std::cout << "  Eventos:\n";

    printEventList(voice.getEvents());
    std::cout << '\n';
}

int main() {
    std::cout << "=== Peppertune ===\n\n";

    MusicContext contexto;
    TextInterpreter interpreter(contexto);
    MidiGenerator midiGenerator;

    const std::string input =
        "C D E F\n"
        "[4] G A B C\n"
        "[8] C?DVE";

    std::cout << "Texto de entrada da demonstracao\n";
    printSeparator();
    std::cout << "linha 0: C D E F\n";
    std::cout << "linha 1: [4] G A B C\n";
    std::cout << "linha 2: [8] C?DVE\n\n";

    interpreter.loadText(input);
    interpreter.interpret();

    const auto& voices = interpreter.getVoices();
    const auto voiceEvents = interpreter.getVoiceEvents();

    std::cout << "\nResumo da interpretacao por voz\n";
    printSeparator();
    std::cout << "Total de vozes: " << voices.size() << '\n';
    std::cout << "BPM global final: " << contexto.getBpm() << "\n\n";

    for (const auto& voice : voices) {
        printVoiceSummary(voice);
    }

    std::cout << "[Execucao MIDI]\n";
    printSeparator();
    midiGenerator.generateAndPlay(voiceEvents);
    midiGenerator.saveToFile(voiceEvents);

    return 0;
}