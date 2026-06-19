#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"
#include "interface.h"
#include <stdio.h>
#include "TextInterpreter.h"
#include "Constants.h"

int main(int, char**)
{

    interface ui;
    TextInterpreter interpreter;
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
            // Handle play button click
            interpreter.parseString(ui.get_text_input());
            auto voices = interpreter.getVoices();
            for (int i = 0; i < voices.size(); i++) {
                printf("Voice %d processed (ID: %d)\n", i, voices[i].getVoiceID());
            }
        }

        ui.end();
    }

    ui.cleanup();

    return 0;
}