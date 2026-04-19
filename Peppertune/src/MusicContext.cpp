//Arquivo de lógica do MusicContext

#include "MusicContext.h" //De acordo com o protocolo da interface

//Construtor inicial
MusicContext::MusicContext(){
    resetToDefault();
}

void MusicContext::resetToDefault(){
    bpm = 120;
    volume = 80;
    defaultOctave = 5;
    currentOctave = 5;
    currentInstrument = 0;
}

void MusicContext::raiseOctave(){
    if (currentOctave < 9){
        currentOctave++; //Incrementa até 9
    } else{
        currentOctave = defaultOctave; //Do contrário reseta pra 5
    }
}

int MusicContext::getBpm() const{
    return bpm;
}

int MusicContext::getVolume() const{
    return volume;
}

int MusicContext::getCurrentOctave() const{
    return currentOctave;
}

int MusicContext::getCurrentInstrument() const{
    return currentInstrument;
}