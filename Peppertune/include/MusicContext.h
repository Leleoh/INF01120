//Arquivo de interface do MusicContext
#ifndef MUSICCONTEXT_H
#define MUSICCONTEXT_H

class MusicContext{
    private:
    int voiceID;
    int volume;
    int currentOctave;
    int currentInstrument;

    public:
    MusicContext(int id); //Exige id para saber quando surgir

    //Ações
    void setInstrument(int newInstrumet);
    void raiseOctave();
    void doubleVolume();
    void lowerOctave();

    //Ler o estado
    int getVoiceID() const;
    int getVolume() const;
    int getCurrentOctave() const;
    int getCurrentInstrument() const;
};

#endif