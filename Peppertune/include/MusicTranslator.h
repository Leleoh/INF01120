#ifndef MUSICTRANSLATOR_H
#define MUSICTRANSLATOR_H

#include "MusicContext.h"
#include "Voice.h"

class MusicTranslator {
public:
    static void translateChar(char c, Voice& voice, MusicContext& ctx);

private:
    static std::string noteToPitch(char noteChar, int octave);
    static bool isNoteChar(char c);
    static bool isPauseChar(char c);
    static bool isUnmappedVowel(char c);

    static void handleNote(char c, Voice& voice);
    static void handlePause(char c, Voice& voice);
    static void handleInstrumentChange(char c, Voice& voice);
    static void handleOctaveChange(char c, Voice& voice);
    static void handleVolumeChange(char c, Voice& voice);
    static void handleBpmChange(int delta, Voice& voice, MusicContext& ctx);
    static void handleRepeatOrPause(char c, Voice& voice);
};

#endif