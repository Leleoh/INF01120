//Arquivo de interface do MusicContext

class MusicContext{
    private:
    int bpm;
    int volume;
    int defaultOctave;
    int currentOctave;
    int currentInstrument;

    public:
    MusicContext();

    void resetToDefault();
    void raiseOctave();
    void doubleVolume();

    int getBpm() const;
    int getVolume() const;
    int getCurrentOctave() const;
    int getCurrentInstrument() const;
};
