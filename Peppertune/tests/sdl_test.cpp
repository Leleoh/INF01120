#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"
#include "interface.h"
#include <stdio.h>

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
        if (ui.spawnPlayButton())
        {
            // Handle play button click
            printf("Play button clicked!\n");
        }

        ui.end();
    }

ui.cleanup();

    return 0;
}