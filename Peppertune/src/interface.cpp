
#include "Constants.h"
#include "interface.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include "stdio.h"
#include <string>





        void interface::begin(){


            height = Peppertune::Constants::TAMANHO_ALTURA;
            width = Peppertune::Constants::TAMANHO_LARGURA;
            SDL_Init(SDL_INIT_VIDEO);

             SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
             SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

              SDL_GL_SetAttribute(
              SDL_GL_CONTEXT_PROFILE_MASK,
             SDL_GL_CONTEXT_PROFILE_CORE);



            window = SDL_CreateWindow(
                "PepperTune",
                width,
                height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
            );
            if (!window)
            {
                printf("Erro ao criar janela: %s\n", SDL_GetError());
                return;
            }

            gl_context = SDL_GL_CreateContext(window);
            if (!gl_context)
            {printf("Erro ao criar contexto OpenGL: %s\n", SDL_GetError());
                return;
            }


        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1);

        IMGUI_CHECKVERSION();

        ImGui::CreateContext();

        ImGui::StyleColorsDark();

        ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
        ImGui_ImplOpenGL3_Init("#version 330");
        }

void interface::events(){

        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT)
                exit(0);
        }
}

void interface::widgets(){
  // Início frame ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();


        ImGui::SetNextWindowSize(
        ImVec2(1280, 720)
            );

        // Interface
        ImGui::Begin("Peppertune");


    ImGuiIO& io = ImGui::GetIO();


        
 ImGui::InputTextMultiline(
    "Coloque sua entrada para gerar a música aqui",
    music_name,
    128,
    ImVec2(width - width/2, height)
);
    
}

const char* interface::get_text_input(){
        return music_name;

}
   
bool interface::play_button(){

    ImGui::SetCursorPos(ImVec2(width - 3*width/8, height/4));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 999.0f);
    ImGui::Button("play", ImVec2(width/4, height/2));
    ImGui::PopStyleVar();
    return ImGui::IsItemClicked();
}

void interface::end(){

    ImGui::End();

        // Renderização
        ImGui::Render();

        int width, height;
        SDL_GetWindowSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);




}

void interface::cleanup(){
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();

    ImGui::DestroyContext();

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);

    SDL_Quit();
}