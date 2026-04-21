//Arquivo main do Peppertune
//Teste de pr
#include <iostream>
#include "MusicContext.h"

int main(){
    MusicContext contexto;
    std::cout << "Volume inicial: " << contexto.getVolume() << std::endl;
    contexto.doubleVolume();
    std::cout << "Volume após dobrar: " << contexto.getVolume() << std::endl;
    return 0;
}