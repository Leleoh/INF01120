//Arquivo de lógica MIDI
#include "MidiGenerator.h"
#include <iostream>

void MidiGenerator::generateAndPlay(const std::vector<std::vector<VoiceEvent>>& voiceEvents) {
    std::cout << "[MidiGenerator] Gerando eventos para "
              << voiceEvents.size() << " vozes.\n";

    std::cout << "[MidiGenerator] Observacao: eventos de BPM foram registrados "
              << "nas vozes; a consolidacao do BPM global entre vozes sera "
              << "tratada nesta camada de execucao MIDI.\n";

    for (std::size_t i = 0; i < voiceEvents.size(); ++i) {
        std::cout << "[MidiGenerator] Voz " << i
                  << " | total de eventos = " << voiceEvents[i].size()
                  << '\n';
    }
}

void MidiGenerator::saveToFile(const std::vector<std::vector<VoiceEvent>>& voiceEvents,
                               const std::string& filename) {
    std::cout << "[MidiGenerator] Salvando "
              << voiceEvents.size()
              << " vozes no arquivo: " << filename << '\n';

    std::cout << "[MidiGenerator] Observacao: a consolidacao final de BPM global "
              << "entre vozes sera aplicada na etapa de escrita MIDI.\n";
}