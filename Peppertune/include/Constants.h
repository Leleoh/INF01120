#pragma once

namespace Peppertune::Constants{

    //Valores globais de áudio
    constexpr int MAX_VOLUME = 127;
    constexpr int DEFAULT_VOLUME = 80;

    //Perfis de voz
    constexpr int MAX_VOICE_PROFILES = 4; //Ciclos (rodízio) 0,1,2,3

    // Instrumentos MIDI
    constexpr int INSTRUMENT_PIANO = 0;
    constexpr int INSTRUMENT_HARPSICHORD = 6;
    constexpr int INSTRUMENT_TUBULAR_BELLS = 15;
    constexpr int INSTRUMENT_CHURCH_ORGAN = 20;
    constexpr int INSTRUMENT_HARMONICA = 22;
    constexpr int INSTRUMENT_BASSOON = 70;

    //Regras de oitava
    constexpr int MAX_OCTAVE = 9;
    constexpr int MIN_OCTAVE = 0;
    constexpr int DEFAULT_OCTAVE = 5;

    //Configurações inicias
    inline constexpr int DEFAULT_BPM = 120;
    inline constexpr int BPM_STEP = 10;
    inline constexpr int TAMANHO_LARGURA = 1280;
    inline constexpr int TAMANHO_ALTURA = 720;
}