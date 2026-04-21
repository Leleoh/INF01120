//Arquivo de lógica do MusicContext

#include "MusicContext.h" //De acordo com o protocolo da interface

//Construtor inicial
MusicContext::MusicContext(int id){
    voiceID = id;

    int ciclo = id % 4;

    if (ciclo == 0){
        currentOctave = 6;
        volume = 100;
        currentInstrument = 6;  //Cravo
    }
    else if(ciclo == 1){
        currentOctave = 5;
        volume = 80;
        currentInstrument = 20; //Órgão
    }
    else if(ciclo == 2){
        currentOctave = 4;
        volume = 60;
        currentInstrument = 0;  //Piano
    }
    else if(ciclo == 3){
        currentOctave = 3;
        volume = 40;
        currentInstrument = 70;  //Fagote
    }
}

//Controle de oitavas
void MusicContext::raiseOctave(){
    if (currentOctave < 9){
        currentOctave++; //Incrementa até 9
    }
}

void MusicContext::lowerOctave(){
    if (currentOctave > 0){
        currentOctave--;
    }
}

//Volume
void MusicContext::doubleVolume(){
    if (volume * 2 <= 127){
        volume = volume * 2;
    } else{
        volume = 127;   //Volume no máximo
    }
}

//Instrumento
void MusicContext::setInstrument(int newInstrument){
    if (newInstrument >= 0 && newInstrument <= 127){
        currentInstrument = newInstrument;
    }
}


//Gets
int MusicContext::getVoiceID() const {
    return voiceID;
}

int MusicContext::getVolume() const {
    return volume;
}

int MusicContext::getCurrentOctave() const {
    return currentOctave;
}

int MusicContext::getCurrentInstrument() const {
    return currentInstrument;
}