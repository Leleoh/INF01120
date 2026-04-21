//Arquivo de interface do MusicContext

#pragma once

class MusicContext {
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
    void setInstrument(int instrument);   //Para general MIDI

    int getBpm() const;
    int getVolume() const;
    int getCurrentOctave() const;
    int getCurrentInstrument() const;
};