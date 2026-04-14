# Versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(Peppertune)

# Ensina o compilador onde estão os "contratos" (.h)
include_directories(include)

# Pega automaticamente todos os arquivos .cpp da pasta src
file(GLOB SOURCES "src/*.cpp")

# Cria o executável final juntando tudo
add_executable(peppertune ${SOURCES})