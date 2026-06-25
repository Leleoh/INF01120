//Arquivo de lógica do MusicContext

#include "MusicContext.h" //De acordo com o protocolo da interface

//Construtor inicial
MusicContext::MusicContext(int id){
    voiceID = id;
    bpm = 120; // Default BPM
    
    int ciclo = id % 4;
    if (ciclo == 0){
        // currentInstrument = 6;  //Cravo
    } else if(ciclo == 1){
        // currentInstrument = 20; //Órgão
    } else if(ciclo == 2){
        // currentInstrument = 0;  //Piano
    } else if(ciclo == 3){
        // currentInstrument = 70;  //Fagote
    }
    currentOctave = baseOctave;
}

//Controle de oitavas
void MusicContext::raiseOctave(){
    if (currentOctave < 9){
        currentOctave++;
    } else {
        currentOctave = baseOctave;
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

// Setters da UI (TextInterpreter)
void MusicContext::setVolume(int newVolume){
    if (newVolume >= 0 && newVolume <= 127) volume = newVolume;
}

void MusicContext::setBaseOctave(int newOctave){
    if (newOctave >= 0 && newOctave <= 9) baseOctave = newOctave;
}

void MusicContext::setCurrentOctave(int newOctave){
    if (newOctave >= 0 && newOctave <= 9) currentOctave = newOctave;
}

//MARK: Gets
int MusicContext::getVoiceID() const {
    return voiceID;
}

int MusicContext::getVolume() const {
    return volume;
}

int MusicContext::getBaseOctave() const {
    return baseOctave;
}

int MusicContext::getCurrentOctave() const {
    return currentOctave;
}

int MusicContext::getCurrentInstrument() const {
    return currentInstrument;
}

// BPM
int MusicContext::getBpm() const {
    return bpm;
}

void MusicContext::setBpm(int newBpm) {
    bpm = newBpm;
}

void MusicContext::increaseBpm(int delta) {
    bpm += delta;
}

void MusicContext::decreaseBpm(int delta) {
    if (bpm - delta > 0) {
        bpm -= delta;
    }
}