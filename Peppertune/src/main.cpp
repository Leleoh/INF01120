//Arquivo main do Peppertune
#include <iostream>
#include "MusicContext.h"
#include "MusicTranslator.h"

int main(){
    
    MusicContext testeVoz(0);
    int bpmAtual = 120;


    //Parâmetros iniciais
    std::cout << "--Estado inicial--" << std::endl;
    std::cout << "Instrumento: " << testeVoz.getCurrentInstrument() << std::endl;
    std::cout << "Volume: " << testeVoz.getVolume() << std::endl;
    std::cout << "BPM: " << bpmAtual << std::endl;

    //Transformações
    MusicTranslator::applyMapping('!', testeVoz, bpmAtual); //Muda para harmonica (22)
    MusicTranslator::applyMapping(' ', testeVoz, bpmAtual); //Dobra volume
    MusicTranslator::applyMapping('<', testeVoz, bpmAtual); //Desacelera BPM


    //Resultados
    std::cout << "\n--- APOS TRADUCAO (!, Espaco e <) ---" << std::endl;
    std::cout << "Instrumento (deve ser 22): " << testeVoz.getCurrentInstrument() << std::endl;
    std::cout << "Volume (deve travar em 127): " << testeVoz.getVolume() << std::endl; 
    std::cout << "BPM (deve cair para 110): " << bpmAtual << std::endl;


    return 0;

}