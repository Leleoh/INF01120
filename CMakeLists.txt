cmake_minimum_required(VERSION 3.14)

project(Peppertune LANGUAGES C CXX)

if(MSVC)
    add_compile_options(/FS)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# ---- SDL3 ----
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.16
)
FetchContent_MakeAvailable(SDL3)

# ---- ImGui ----
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

# ---- Midifile removido do FetchContent, agora incluso diretamente no src/ ----

# ---- OpenGL ----
find_package(OpenGL REQUIRED)

# Encontra todos os arquivos .cpp dentro de Peppertune/src
file(GLOB_RECURSE SOURCES "Peppertune/src/*.cpp")

# Cria o executável principal
add_executable(peppertune

    ${SOURCES}

    # -----------------------------
    # ImGui Core
    # -----------------------------
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp

    # -----------------------------
    # Backends SDL3 + OpenGL3
    # -----------------------------
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# Inclui a pasta de headers para o executável principal
target_include_directories(peppertune PRIVATE
    Peppertune/include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    Peppertune/include/midifile
)

# Define o padrão C++
target_compile_features(peppertune PRIVATE cxx_std_17)


# ---------------------------------------------------------
# Linkagem das bibliotecas
# ---------------------------------------------------------
target_link_libraries(peppertune PRIVATE
    SDL3::SDL3
    OpenGL::GL
)

# ---------------------------------------------------------
# Executável de testes
# ---------------------------------------------------------
add_executable(peppertune_tests
    Peppertune/tests/sdl_test.cpp
    Peppertune/src/interface.cpp
    Peppertune/src/tinyfiledialogs.cpp
    
    



    # -----------------------------
    # ImGui Core
    # -----------------------------
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp

    # -----------------------------
    # Backends SDL3 + OpenGL3
    # -----------------------------
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp



)


# Inclui a pasta de headers TAMBÉM para o executável de testes
target_include_directories(peppertune_tests PRIVATE
    Peppertune/include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    Peppertune/include/midifile
)


# Define o padrão C++ TAMBÉM para o executável de testes
target_compile_features(peppertune_tests PRIVATE cxx_std_17)

target_link_libraries(peppertune_tests PRIVATE
    SDL3::SDL3
    OpenGL::GL
)
#teste aleatorio para ver se o github ta funcionando

if(WIN32)
    foreach(target peppertune peppertune_tests)
        add_custom_command(
            TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${target}>
                $<TARGET_FILE_DIR:${target}>
            COMMAND_EXPAND_LISTS
        )
    endforeach()
endif()
