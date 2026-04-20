cmake_minimum_required(VERSION 3.14)

project(Peppertune LANGUAGES CXX)

# Encontra todos os arquivos .cpp dentro de Peppertune/src
file(GLOB SOURCES "Peppertune/src/*.cpp")

# Cria o executável
add_executable(peppertune ${SOURCES})

# Inclui a pasta de headers
target_include_directories(peppertune PRIVATE Peppertune/include)

# Define o padrão C++
target_compile_features(peppertune PRIVATE cxx_std_17)