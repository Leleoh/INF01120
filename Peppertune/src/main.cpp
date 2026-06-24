//Arquivo main do Peppertune
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include "MusicContext.h"
#include "MusicTranslator.h"
#include "TextInterpreter.h"
#include "MidiGenerator.h"
#include "interface.h"

int main(){
    // 1. Inicia a interface
    interface ui;
    ui.begin();

    std::atomic<bool> isPlaying(false);

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
            ui.setErrorWindow(true, "Funcao de gerar MIDI ainda nao implementada! Use o botao PLAY para gerar e tocar o MIDI a partir do texto digitado.");
        }

        if(ui.spawnPauseButton()) {
            ui.setErrorWindow(true, "Funcao de pausar MIDI ainda nao implementada!");
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

                // Cria uma thread e faz o detach para rodar em paralelo sem bloquear a main
                std::thread([textoInput, bpmInput, octaveInput, volumeInput, &isPlaying]() {
                    // Passo B: O maestro agora lê a string copiada
                    TextInterpreter maestro;
                    
                    // Passando as configurações da interface para o backend!
                    maestro.setInitialBPM(bpmInput);
                    maestro.setInitialOctave(octaveInput);
                    maestro.setInitialVolume(volumeInput);
                    
                    maestro.parseString(textoInput.c_str());
                    
                    // Passo E: Gerar MIDI e tocar
                    MidiGenerator midi;
                    midi.generateAndPlay(maestro.getAllVoiceEvents());
                    
                    isPlaying = false; // Libera o play quando terminar
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