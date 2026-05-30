#pragma once

namespace Peppertune::Constants{

    //Valores globais de áudio
    inline constexpr int MAX_VOLUME = 127;
    inline constexpr int DEFAULT_VOLUME = 80;

    //Perfis de voz
    inline constexpr int MAX_VOICE_PROFILES = 4; //Ciclos (rodízio) 0,1,2,3

    // Instrumentos MIDI
    inline constexpr int INSTRUMENT_PIANO = 0;
    inline constexpr int INSTRUMENT_HARPSICHORD = 6;
    inline constexpr int INSTRUMENT_TUBULAR_BELLS = 15;
    inline constexpr int INSTRUMENT_CHURCH_ORGAN = 20;
    inline constexpr int INSTRUMENT_HARMONICA = 22;
    inline constexpr int INSTRUMENT_BASSOON = 70;

    //Regras de oitava
    inline constexpr int MAX_OCTAVE = 9;
    inline constexpr int MIN_OCTAVE = 0;
    inline constexpr int DEFAULT_OCTAVE = 5;

    //Configurações inicias
    inline constexpr int DEFAULT_BPM = 120;
    inline constexpr int BPM_STEP = 10;
    inline constexpr int TAMANHO_LARGURA = 1280;
    inline constexpr int TAMANHO_ALTURA = 720;
}