#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include "MusicTranslator.h"
#include "TextInterpreter.h"
#include "MidiGenerator.h"
#include "interface.h"
#include "tinyfiledialogs.h"

int main(){
    // 1. Inicia a interface
    interface ui;
    ui.begin();

    std::atomic<bool> isPlaying(false);
    std::atomic<bool> isPaused(false);

    // Loop principal (Game Loop)
    while (true) {
        ui.events(); // Lê comandos do teclado/mouse e tratar fechamento de janela
        ui.widgets(); // Inicia o frame da interface
        
        // Coloca os componentes na tela
        ui.spawnTextInput();
        ui.spawnBpmWidget();
        ui.spawnOctaveWidget();
        ui.spawnVolumeWidget();
        ui.spawnSaveButton();
        ui.spawnLoadButton();
        ui.spawnErrorMessage(); // Verifica se showErrorWindow é true e, se for, mostra a janela de erro com a mensagem armazenada em errorMessage
        
        // Verifica se o botão play foi clicado neste frame

        if(ui.spawnGenerateMidiButton()) {
            const char* filterPatterns[1] = {"*.mid"};
            const char* path = tinyfd_saveFileDialog("Save MIDI file", "music.mid", 1, filterPatterns, "MIDI files");
            if (path) {
                std::cout << "[Main] Botao Generate MIDI pressionado! Salvando em: " << path << std::endl;
                
                std::string textoInput = ui.get_text_input();
                int bpmInput = ui.getBpmInput();
                int octaveInput = ui.getOctaveInput();
                int volumeInput = ui.getVolumeInput();

                TextInterpreter maestro;
                maestro.setInitialBPM(bpmInput);
                maestro.setInitialOctave(octaveInput);
                maestro.setInitialVolume(volumeInput);
                maestro.parseString(textoInput.c_str());

                MidiGenerator midi;
                midi.saveToFile(maestro.getAllVoiceEvents(), path);
            }
        }

        if(ui.spawnPauseButton()) {
            if (isPlaying) {
                isPaused = !isPaused; // Inverte o estado de pause
                std::cout << "[Main] Musica " << (isPaused ? "pausada" : "retomada") << "!" << std::endl;
            } else {
                ui.setErrorWindow(true, "Nenhuma musica tocando para pausar!");
            }
        }

        if (ui.spawnPlayButton()) {
            if (!isPlaying) {
                std::cout << "[Main] Botao Play pressionado!" << std::endl;
                
                // Salvamos os inputs em variáveis locais para passarmos por cópia para a thread
                std::string textoInput = ui.get_text_input();
                int bpmInput = ui.getBpmInput();
                int octaveInput = ui.getOctaveInput();
                int volumeInput = ui.getVolumeInput();
                
                isPlaying = true; // Bloqueia novos plays até terminar
                isPaused = false; // Reseta o estado de pause

                // Cria uma thread e faz o detach para rodar em paralelo sem bloquear a main
                std::thread([textoInput, bpmInput, octaveInput, volumeInput, &isPlaying, &isPaused]() {
                    // Passo B: O maestro agora lê a string copiada
                    TextInterpreter maestro;
                    
                    // Passando as configurações da interface para o backend!
                    maestro.setInitialBPM(bpmInput);
                    maestro.setInitialOctave(octaveInput);
                    maestro.setInitialVolume(volumeInput);
                    
                    maestro.parseString(textoInput.c_str());
                    
                    // Passo E: Gerar MIDI e tocar
                    MidiGenerator midi;
                    midi.generateAndPlay(maestro.getAllVoiceEvents(), &isPaused);
                    
                    isPlaying = false; // Libera o play quando terminar
                    isPaused = false;
                }).detach();
            } else {
                std::cout << "[Main] O audio ja esta tocando! Aguarde o termino." << std::endl;
            }
        }
        
        ui.end(); // Renderiza tudo e finaliza o frame
    }

    ui.cleanup();
    return 0;
}