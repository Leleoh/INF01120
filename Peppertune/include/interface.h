#pragma once

#include "Constants.h"

#include <SDL3/SDL.h>

class interface{
    public:
        SDL_Window* window;
        int  width;
        int  height;
        SDL_GLContext gl_context;
        SDL_Event event;
        char music_name[128];
    public:
        void begin();
        void events();
        void widgets();
        void end();
        void cleanup();
        const char* get_text_input();
        bool play_button();

};