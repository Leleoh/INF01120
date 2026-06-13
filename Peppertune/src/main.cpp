//Arquivo main do Peppertune
#include <iostream>
#include <fstream>
#include "MusicContext.h"
#include "MusicTranslator.h"
#include "TextInterpreter.h"
#include "MidiGenerator.h"
#include "interface.h"

int main(){
    // 1. Inicia a interface
    interface ui;
    ui.begin();

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
        ui.SpawnLoadButton();
        
        // Verifica se o botão play foi clicado neste frame
        if (ui.spawnPlayButton()) {
            std::cout << "[Main] Botao Play pressionado!" << std::endl;
            
            // Passo A: Pegar o texto digitado na interface
            const char* textoInput = ui.get_text_input();
            
            // Passo B: O maestro agora lê a string diretamente da interface
            TextInterpreter maestro;
            
            // Passando as configurações da interface para o backend!
            maestro.setInitialBPM(ui.getBpmInput());
            maestro.setInitialOctave(ui.getOctaveInput());
            maestro.setInitialVolume(ui.getVolumeInput());
            
            maestro.parseString(textoInput);
            
            // Passo E: Gerar MIDI e tocar
            MidiGenerator midi;
            midi.generateAndPlay(maestro.getAllVoiceEvents());
        }
        
        ui.end(); // Renderiza tudo e finaliza o frame
    }

    ui.cleanup();
    return 0;
}