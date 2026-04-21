//Arquivo de lógica do MusicContext

#include "MusicContext.h"

MusicContext::MusicContext() {
    resetToDefault();
}

void MusicContext::resetToDefault() {
    bpm = 120;
    volume = 80;
    defaultOctave = 5;
    currentOctave = 5;
    currentInstrument = 0;        //Piano (general MIDI 0)
}

void MusicContext::raiseOctave() {
    if (currentOctave < 9) {
        currentOctave++;
    } else {
        currentOctave = defaultOctave;
    }
}

void MusicContext::doubleVolume() {
    if (volume * 2 <= 127) {
        volume = volume * 2;
    } else {
        volume = 127;
    }
}

void MusicContext::setInstrument(int instrument) {
    if (instrument >= 0 && instrument <= 127) {
        currentInstrument = instrument;
    }
}

int MusicContext::getBpm() const { return bpm; }
int MusicContext::getVolume() const { return volume; }
int MusicContext::getCurrentOctave() const { return currentOctave; }
int MusicContext::getCurrentInstrument() const { return currentInstrument; }