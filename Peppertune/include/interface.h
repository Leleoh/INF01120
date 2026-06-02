#pragma once

#include "Constants.h"

#include <SDL3/SDL.h>

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
        //Getters
        int getBpmInput();
        const char* get_text_input();
        int getOctaveInput();
        int getVolumeInput();


};