
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
#include "tinyfiledialogs.h"
#include <fstream>



        void interface::begin(){


            height = Peppertune::Constants::TAMANHO_ALTURA;
            width = Peppertune::Constants::TAMANHO_LARGURA;
            startingBpm = Peppertune::Constants::DEFAULT_BPM;
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



        //processa os eventos do SDL3, como o fechamento da janela.
void interface::events(){

        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT)
                exit(0);
        }
}

    //Configura IMGUI para spawnar os widgets e o inicializa para o SDL3 e OpenGL.
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


    
}
//Spawna caixa de texto para input de música.
 void interface::spawnTextInput(){   
  ImGui::InputTextMultiline(
     "Coloque os parâmetros da música aqui",
     music_name,
     128,
     ImVec2(static_cast<float>(width - width/2), static_cast<float>(height))
 );
 }
//get de dados de input de música.
const char* interface::get_text_input(){
        return music_name;

}
//Spawna caixa de int para input de BPM.
void interface::spawnBpmWidget(){
    ImGui::SetCursorPos(ImVec2(static_cast<float>(width/2 + width/72), static_cast<float>(height/12)));
    ImGui::SetNextItemWidth(static_cast<float>(width/8));
    ImGui::InputInt("BPM", &startingBpm);

        //Não deixa o usuário colocar um BPM fora dos limites pré-definidos.
        if (startingBpm > Peppertune::Constants::MAX_BPM) {
            startingBpm = Peppertune::Constants::MAX_BPM;
        }
        else if (startingBpm < Peppertune::Constants::MIN_BPM) {
            startingBpm = Peppertune::Constants::MIN_BPM;
        }
}

//get de dados de input de BPM.
int interface::getBpmInput(){
    return startingBpm;
}

//spawna bottão de play
bool interface::spawnPlayButton(){

    ImGui::SetCursorPos(ImVec2(static_cast<float>(width - 3*width/8), static_cast<float>(height/4)));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 999.0f);
    ImGui::Button("play", ImVec2(static_cast<float>(width/4), static_cast<float>(height/2)));
    ImGui::PopStyleVar();
    return ImGui::IsItemClicked();
}


//spawna caixa de int para input de oitava.
void interface::spawnOctaveWidget(){
    ImGui::SetCursorPos(ImVec2(static_cast<float>(width/2 + width/6), static_cast<float>(height/12)));
    ImGui::SetNextItemWidth(static_cast<float>(width/8));
    ImGui::InputInt("OCTAVE", &startingOctave);

        //Não deixa o usuário colocar uma oitava fora dos limites pré-definidos.
        if (startingOctave > Peppertune::Constants::MAX_OCTAVE) {
            startingOctave = Peppertune::Constants::MAX_OCTAVE;
        }
        else if (startingOctave < Peppertune::Constants::MIN_OCTAVE) {
            startingOctave = Peppertune::Constants::MIN_OCTAVE;
        }
}

//get de dados de input de oitava.
int interface::getOctaveInput(){
    return startingOctave;
}


//spawna caixa de int para input de volume.
void interface::spawnVolumeWidget(){
    ImGui::SetCursorPos(ImVec2(static_cast<float>(width/2 + width/3), static_cast<float>(height/12)));
    ImGui::SetNextItemWidth(static_cast<float>(width/8));
    ImGui::InputInt("VOLUME", &startingVolume);

        //Não deixa o usuário colocar um volume fora dos limites pré-definidos.
        if (startingVolume > Peppertune::Constants::MAX_VOLUME) {
            startingVolume = Peppertune::Constants::MAX_VOLUME;
        }
        else if (startingVolume < Peppertune::Constants::MIN_VOLUME) {
            startingVolume = Peppertune::Constants::MIN_VOLUME;
        }
}

//get de dados de input de volume.
int interface::getVolumeInput(){
    return startingVolume;
}



void interface::spawnSaveButton(){
    ImGui::SetCursorPos(ImVec2(static_cast<float>(width/2 + width/9), static_cast<float>(height/2 + height/3)));
    ImGui::SetNextItemWidth(static_cast<float>(width/8));
    ImGui::Button("SAVE", ImVec2(static_cast<float>(width/8), static_cast<float>(height/12)));
    if (ImGui::IsItemClicked()) {
        saveFile();
    }
}

void interface::SpawnLoadButton(){
    ImGui::SetCursorPos(ImVec2(static_cast<float>(width/2 + width/4), static_cast<float>(height/2 + height/3)));
    ImGui::SetNextItemWidth(static_cast<float>(width/8));
    ImGui::Button("LOAD", ImVec2(static_cast<float>(width/8), static_cast<float>(height/12)));
    if (ImGui::IsItemClicked()) {
        loadFile();
    }
}

//Finaliza o frame do ImGui, renderiza e atualiza a janela.
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

//termina os processos de janela e contexto do SDL3 e OpenGL, além de destruir a janela.
void interface::cleanup(){
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();

    ImGui::DestroyContext();

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);

    SDL_Quit();
}


    void interface::saveFile(){

        {

    const char* path = tinyfd_saveFileDialog(
        "Save text file",
        "file.txt",
        0,
        NULL,
        NULL
    );

    if(path) {
        std::ofstream file(path);
        file << get_text_input() << std::endl;
    }
}
    }

    void interface::loadFile(){
    const char* filterPatterns[] = {"*.txt"};
    const char* filePath = tinyfd_openFileDialog(
        "Open text file",
        "",
        1,
        filterPatterns,
        "Text files",
        0
    );

    if (!filePath)
        printf("No file selected\n");

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Could not open file\n";
    }


    file.read(music_name, sizeof(music_name) - 1);

    // important: terminate the C string
    music_name[file.gcount()] = '\0';


    file.close();

}