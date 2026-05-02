#include "MusicTranslator.h"
#include "Constants.h"

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
        currentVoice.setInstrument(Peppertune::Constants::INSTRUMENT_HARMONICA); //Harmonica
        break;

    case ';':
        currentVoice.setInstrument(Peppertune::Constants::INSTRUMENT_TUBULAR_BELLS); //Tubular bells
        break;

    case ',':
        currentVoice.setInstrument(Peppertune::Constants::INSTRUMENT_CHURCH_ORGAN); //Church organ
        break;


    //Controles de BPM
    case '>':
        globalBPM += Peppertune::Constants::BPM_STEP; //Aumenta o bpm
        break;
    
    case '<':
        globalBPM -= Peppertune::Constants::BPM_STEP; //Diminui o bpm
        break;

    //Caracteres para notas e pausas (FUTURAMENTE)
    
        
    default:    //Vogais e letras não mapeadas
        break;
    }


}