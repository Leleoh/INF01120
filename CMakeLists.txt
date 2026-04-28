cmake_minimum_required(VERSION 3.14)

project(Peppertune LANGUAGES CXX)

# Encontra todos os arquivos .cpp dentro de Peppertune/src
file(GLOB SOURCES "Peppertune/src/*.cpp")

# Cria o executável principal
add_executable(peppertune ${SOURCES})

# Inclui a pasta de headers
target_include_directories(peppertune PRIVATE Peppertune/include)

# Define o padrão C++
target_compile_features(peppertune PRIVATE cxx_std_17)

# Executável de testes
add_executable(peppertune_tests
    Peppertune/tests/test.cpp
    Peppertune/src/MusicContext.cpp
    Peppertune/src/TextInterpreter.cpp
    Peppertune/src/Voice.cpp
)

# Inclui a pasta de headers também para os testes
target_include_directories(peppertune_tests PRIVATE Peppertune/include)

# Define o padrão C++ também para os testes
target_compile_features(peppertune_tests PRIVATE cxx_std_17)