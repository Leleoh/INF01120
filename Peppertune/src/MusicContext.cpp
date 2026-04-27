// Arquivo de lógica do MusicContext
#include "MusicContext.h"

MusicContext::MusicContext() {
    resetToDefault();
}

void MusicContext::resetToDefault() {
    bpm = 120;
}

void MusicContext::setBpm(int newBpm) {
    if (newBpm > 0) {
        bpm = newBpm;
    }
}

void MusicContext::increaseBpm(int delta) {
    if (delta > 0) {
        bpm += delta;
    }
}

void MusicContext::decreaseBpm(int delta) {
    if (delta > 0) {
        bpm = (bpm - delta > 0) ? bpm - delta : 1;
    }
}

int MusicContext::getBpm() const {
    return bpm;
}