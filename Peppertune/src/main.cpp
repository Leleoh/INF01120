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
            
            // Passo B: Salvar em um arquivo temporario (A solução MVP para o parser)
            std::ofstream tempFile("temp_input.txt");
            if (tempFile.is_open()) {
                tempFile << textoInput;
                tempFile.close();
            } else {
                std::cerr << "Erro ao criar arquivo temporario." << std::endl;
            }
            
            // Passo C: Instanciar um maestro NOVO para evitar que as notas da vez passada se acumulem
            TextInterpreter maestro;
            
            // (Futuro) Aqui você passaria os valores dos inputs para o maestro:
            // maestro.setInitialBPM(ui.getBpmInput());
            
            // Passo D: O maestro lê o arquivo que acabamos de salvar
            maestro.parseFile("temp_input.txt");
            
            // Passo E: Gerar MIDI e tocar
            MidiGenerator midi;
            midi.generateAndPlay(maestro.getAllVoiceEvents());
        }
        
        ui.end(); // Renderiza tudo e finaliza o frame
    }

    ui.cleanup();
    return 0;
}