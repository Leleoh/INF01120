//Arquivo de lógica do MusicContext

#include "MusicContext.h" //De acordo com o protocolo da interface

//Construtor inicial
MusicContext::MusicContext(int id){
    voiceID = id;
    

}

//MARK: Gets
int MusicContext::getVoiceID() const {
    return voiceID;
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