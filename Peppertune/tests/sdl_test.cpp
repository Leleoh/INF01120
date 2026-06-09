#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"
#include "interface.h"
#include <stdio.h>
#include "Textparser.h"
#include "Constants.h"

int main(int, char**)
{

    interface ui;
    TextParser parser;
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
        ui.SpawnLoadButton();
        ui.spawnSaveButton();
        if (ui.spawnPlayButton())
        {
            // Handle play button click
            parser.Parse(ui.get_text_input());
            for (int i = 0; i < Peppertune::Constants::MAX_VOICES; i++) {
                printf("Voice %d: %s\n", i, parser.GetVoice(i).c_str());
            }
        }

        ui.end();
    }

ui.cleanup();

    return 0;
}