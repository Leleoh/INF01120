//Arquivo de interface do MusicContext
#ifndef MUSICCONTEXT_H
#define MUSICCONTEXT_H

class MusicContext{
    private:
    int voiceID;
    int volume;
    int currentOctave;
    int currentInstrument;
    int bpm; // Added to satisfy Voice.cpp

    public:
    MusicContext(int id); //Exige id para saber quando surgir

    //Ações

    //Ler o estado
    int getVoiceID() const;

    
    // BPM methods para Voice.cpp
    int getBpm() const;
    void setBpm(int newBpm);
    void increaseBpm(int delta);
    void decreaseBpm(int delta);
};

#endif