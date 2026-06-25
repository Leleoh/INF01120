#include "MusicTranslator.h"
#include "Constants.h"
#include <algorithm>
#include <cctype>

std::string MusicTranslator::noteToPitch(char noteChar, int octave) {
    switch (noteChar) {
        case 'A': return "A" + std::to_string(octave);
        case 'B': return "B" + std::to_string(octave);
        case 'C': return "C" + std::to_string(octave);
        case 'D': return "D" + std::to_string(octave);
        case 'E': return "E" + std::to_string(octave);
        case 'F': return "F" + std::to_string(octave);
        case 'G': return "G" + std::to_string(octave);
        case 'H': return "Bb" + std::to_string(octave);
        default:  return "REST";
    }
}

bool MusicTranslator::isNoteChar(char c) {
    return c >= 'A' && c <= 'H';
}

bool MusicTranslator::isPauseChar(char c) {
    return c >= 'a' && c <= 'h';
}

bool MusicTranslator::isUnmappedVowel(char c) {
    return c == 'O' || c == 'o' ||
           c == 'I' || c == 'i' ||
           c == 'U' || c == 'u';
}

void MusicTranslator::handleNote(char c, Voice& voice, MusicContext& ctx) {
    voice.setLastNote(c);

    voice.addEvent({
        VoiceEventType::Note,
        voice.getVoiceId(),
        voice.getCurrentBeat(),
        c,
        noteToPitch(c, ctx.getCurrentOctave()),
        1,
        ctx.getVolume(),
        ctx.getCurrentInstrument(),
        -1,
        ctx.getCurrentOctave()
    });

    voice.setCurrentBeat(voice.getCurrentBeat() + 1);
}

void MusicTranslator::handlePause(char c, Voice& voice, MusicContext& ctx) {
    voice.addEvent({
        VoiceEventType::Rest,
        voice.getVoiceId(),
        voice.getCurrentBeat(),
        c,
        "",
        1,
        ctx.getVolume(),
        ctx.getCurrentInstrument(),
        -1,
        ctx.getCurrentOctave()
    });

    voice.setCurrentBeat(voice.getCurrentBeat() + 1);
}

void MusicTranslator::handleInstrumentChange(char c, Voice& voice, MusicContext& ctx) {
    if (c == '!') {
        ctx.setInstrument(22);
    } else if (c == ';') {
        ctx.setInstrument(15);
    } else if (c == ',') {
        ctx.setInstrument(20);
    } else if (isUnmappedVowel(c)) {
        ctx.setInstrument(110);
    }

    voice.addEvent({
        VoiceEventType::InstrumentChange,
        voice.getVoiceId(),
        voice.getCurrentBeat(),
        c,
        "",
        0,
        ctx.getVolume(),
        ctx.getCurrentInstrument(),
        -1,
        ctx.getCurrentOctave()
    });
}

void MusicTranslator::handleOctaveChange(char c, Voice& voice, MusicContext& ctx) {
    if (c == '?' || c == '.') {
        ctx.raiseOctave();
    } else if (c == 'V') {
        ctx.lowerOctave();
    }

    voice.addEvent({
        VoiceEventType::OctaveChange,
        voice.getVoiceId(),
        voice.getCurrentBeat(),
        c,
        "",
        0,
        ctx.getVolume(),
        ctx.getCurrentInstrument(),
        -1,
        ctx.getCurrentOctave()
    });
}

void MusicTranslator::handleVolumeChange(char c, Voice& voice, MusicContext& ctx) {
    if (c == ' ') {
        ctx.doubleVolume();

        voice.addEvent({
            VoiceEventType::VolumeChange,
            voice.getVoiceId(),
            voice.getCurrentBeat(),
            c,
            "",
            0,
            ctx.getVolume(),
            ctx.getCurrentInstrument(),
            -1,
            ctx.getCurrentOctave()
        });
    }
}

void MusicTranslator::handleBpmChange(int delta, Voice& voice, MusicContext& ctx) {
    if (delta > 0) {
        ctx.increaseBpm(delta);
    } else {
        ctx.decreaseBpm(-delta);
    }

    voice.addEvent({
        VoiceEventType::BpmChange,
        voice.getVoiceId(),
        voice.getCurrentBeat(),
        '\0',
        "",
        0,
        ctx.getVolume(),
        ctx.getCurrentInstrument(),
        ctx.getBpm(),
        ctx.getCurrentOctave()
    });
}

void MusicTranslator::handleRepeatOrPause(char c, Voice& voice, MusicContext& ctx) {
    if (voice.getLastNote() != '\0') {
        voice.addEvent({
            VoiceEventType::RepeatLastNote,
            voice.getVoiceId(),
            voice.getCurrentBeat(),
            c,
            noteToPitch(voice.getLastNote(), ctx.getCurrentOctave()),
            1,
            ctx.getVolume(),
            ctx.getCurrentInstrument(),
            -1,
            ctx.getCurrentOctave()
        });
    } else {
        voice.addEvent({
            VoiceEventType::Rest,
            voice.getVoiceId(),
            voice.getCurrentBeat(),
            c,
            "",
            1,
            ctx.getVolume(),
            ctx.getCurrentInstrument(),
            -1,
            ctx.getCurrentOctave()
        });
    }

    voice.setCurrentBeat(voice.getCurrentBeat() + 1);
}

void MusicTranslator::translateChar(char c, Voice& voice, MusicContext& ctx) {
    if (isNoteChar(c)) {
        handleNote(c, voice, ctx);
        return;
    }

    if (isPauseChar(c)) {
        handlePause(c, voice, ctx);
        return;
    }

    if (c == '!' || c == ';' || c == ',' || isUnmappedVowel(c)) {
        handleInstrumentChange(c, voice, ctx);
        return;
    }

    if (c == '?' || c == 'V' || c == '.') {
        handleOctaveChange(c, voice, ctx);
        return;
    }

    if (c == ' ') {
        handleVolumeChange(c, voice, ctx);
        return;
    }

    if (c == '>') {
        handleBpmChange(10, voice, ctx);
        return;
    }

    if (c == '<') {
        handleBpmChange(-10, voice, ctx);
        return;
    }

    if (!std::isspace(static_cast<unsigned char>(c))) {
        handleRepeatOrPause(c, voice, ctx);
    }
}