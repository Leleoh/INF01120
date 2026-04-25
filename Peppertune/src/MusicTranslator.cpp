#include "MusicTranslator.h"

//Função responsável por chamar as funções do MusicContext a partir dos parâmetros
void MusicTranslator::applyMapping(char letter, MusicContext& currentVoice, int& globalBPM){

    switch (letter)
    {
    case '?':
        currentVoice.raiseOctave();
        break;
    
    case 'V':
        currentVoice.lowerOctave();
        break;

    case ' ':   //Espaço
        currentVoice.doubleVolume();
        break;

    case '!':
        currentVoice.setInstrument(22); //Harmonica
        break;

    case ';':
        currentVoice.setInstrument(15); //Tubular bells
        break;

    case ',':
        currentVoice.setInstrument(20); //Church organ
        break;


    //Controles de BPM
    case '>':
        globalBPM += 10; //Aumenta o bpm
        break;
    
    case '<':
        globalBPM -= 10; //Diminui o bpm
        break;

    //Caracteres para notas e pausas (FUTURAMENTE)
    
        
    default:    //Vogais e letras não mapeadas
        break;
    }


}