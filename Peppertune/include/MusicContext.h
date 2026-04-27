// Arquivo de interface do MusicContext
#pragma once

class MusicContext {
private:
    int bpm;

public:
    MusicContext();

    void resetToDefault();
    void setBpm(int newBpm);
    void increaseBpm(int delta = 10);
    void decreaseBpm(int delta = 10);

    int getBpm() const;
};