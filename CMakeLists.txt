cmake_minimum_required(VERSION 3.14)

project(Peppertune LANGUAGES CXX)

# Encontra todos os arquivos .cpp dentro de Peppertune/src
file(GLOB SOURCES "Peppertune/src/*.cpp")

# Cria o executável principal
add_executable(peppertune ${SOURCES})

# Inclui a pasta de headers para o executável principal
target_include_directories(peppertune PRIVATE Peppertune/include)

# Define o padrão C++
target_compile_features(peppertune PRIVATE cxx_std_17)

# ---------------------------------------------------------
# Executável de testes
add_executable(peppertune_tests
    Peppertune/tests/test.cpp          # A porta de entrada com o int main()
    Peppertune/src/MusicContext.cpp
    Peppertune/src/TextInterpreter.cpp
    Peppertune/src/MusicTranslator.cpp # O tradutor que faltava
    Peppertune/src/Voice.cpp
)

# Inclui a pasta de headers TAMBÉM para o executável de testes
target_include_directories(peppertune_tests PRIVATE Peppertune/include)

# Define o padrão C++ TAMBÉM para o executável de testes
target_compile_features(peppertune_tests PRIVATE cxx_std_17)