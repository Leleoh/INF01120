#pragma once

#include "Constants.h"

#include <SDL3/SDL.h>
#include <string>

class interface{
    private:
        SDL_Window* window;
        int  width = Peppertune::Constants::TAMANHO_LARGURA;
        int  height = Peppertune::Constants::TAMANHO_ALTURA;
        SDL_GLContext gl_context;
        SDL_Event event;
        char music_name[128] = "Coloque aqui seu input para música";
        int startingBpm = Peppertune::Constants::DEFAULT_BPM;
        int startingOctave = Peppertune::Constants::DEFAULT_OCTAVE;
        int startingVolume = Peppertune::Constants::DEFAULT_VOLUME;
        bool showErrorWindow = false; // variable used to show the error window
        std::string errorMessage; // variable used to store the error message to be shown in the error window
    public:
        //Funções de interface
        void begin();
        void events();
        void widgets();
        void end();
        void cleanup();
        //Spawn de widgets
        bool spawnPlayButton();
        void spawnBpmWidget();
        void spawnTextInput();
        void spawnOctaveWidget();
        void spawnVolumeWidget();
        void spawnSaveButton();
        void spawnLoadButton();
        void spawnErrorMessage(); //makes it so that when showErrorWindow is true, it shows a window with the error message stored in errorMessage variable.
        void setErrorWindow(bool show, const char* message); //sets the error window to show or not. And takes the message to be shown
        //Getters
        int getBpmInput();
        const char* get_text_input();
        int getOctaveInput();
        int getVolumeInput();
        //files
        void saveFile();
        void loadFile();


};