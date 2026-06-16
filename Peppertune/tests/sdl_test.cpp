#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"
#include "interface.h"
#include <stdio.h>
#include "Constants.h"

int main(int, char**)
{

    interface ui;
    ui.begin();

    bool running = true;

    while (running)
    {
        ui.events();
        ui.widgets();
        ui.spawnTextInput();
        ui.spawnBpmWidget();
        ui.spawnOctaveWidget();
        ui.spawnVolumeWidget();
        ui.spawnLoadButton();
        ui.spawnSaveButton();
        ui.spawnErrorMessage();
        if (ui.spawnPlayButton())
        {
            // Aqui você pode adicionar a lógica para iniciar a reprodução da música usando os dados de entrada do usuário.
            ui.setErrorWindow(true,"teste de erro");
            
            }
        

        ui.end();
        
        }

        ui.cleanup();

    return 0;
}