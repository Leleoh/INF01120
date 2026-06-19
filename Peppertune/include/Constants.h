#pragma once

namespace Peppertune::Constants{

    //Valores globais de áudio
    constexpr int MAX_VOLUME = 100;
    constexpr int DEFAULT_VOLUME = 80;
    constexpr int MIN_VOLUME = 0;

    //Perfis de voz
    constexpr int MAX_VOICES = 4; //Ciclos (rodízio) 0,1,2,3

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
    inline constexpr int MAX_BPM = 220;
    inline constexpr int MIN_BPM = 1;
    inline constexpr int TAMANHO_LARGURA = 1280;
    inline constexpr int TAMANHO_ALTURA = 720;

    //constantes de interface
    inline constexpr int OCTAVE_WIDGET_X = 853;
    inline constexpr int OCTAVE_WIDGET_Y = 60;
    inline constexpr int OCTAVE_WIDGET_WIDTH = 160;
    inline constexpr int VOLUME_WIDGET_X = 1066.67;
    inline constexpr int VOLUME_WIDGET_Y = 60;
    inline constexpr int VOLUME_WIDGET_WIDTH = 160;
    inline constexpr int BPM_WIDGET_X = 660;
    inline constexpr int BPM_WIDGET_Y = 60;
    inline constexpr int BPM_WIDGET_WIDTH = 160;
    inline constexpr int SAVE_BUTTON_X = 800;
    inline constexpr int SAVE_BUTTON_Y = 600;
    inline constexpr int LOAD_BUTTON_X = 965;
    inline constexpr int LOAD_BUTTON_Y = 600;
    inline constexpr int SAVE_BUTTON_WIDTH = 160;
    inline constexpr int SAVE_BUTTON_HEIGHT = 60;
    inline constexpr int LOAD_BUTTON_WIDTH = 160;
    inline constexpr int LOAD_BUTTON_HEIGHT = 60;
    inline constexpr int ERROR_MESSAGE_X = 640;
    inline constexpr int ERROR_MESSAGE_Y = 360;
    inline constexpr int ERROR_MESSAGE_WIDTH = 500;
    inline constexpr int ERROR_MESSAGE_HEIGHT = 300;
    inline constexpr int MUSIC_NAME_INPUT_WIDTH = 640;
    inline constexpr int MUSIC_NAME_INPUT_HEIGHT = 720;
    inline constexpr int PLAY_BUTTON_X = 800;
    inline constexpr int PLAY_BUTTON_Y = 320;
    inline constexpr int PLAY_BUTTON_WIDTH = 160;
    inline constexpr int PLAY_BUTTON_HEIGHT = 50;
    inline constexpr int GENERATE_MIDI_BUTTON_X = 800;
    inline constexpr int GENERATE_MIDI_BUTTON_Y = 670;
    inline constexpr int GENERATE_MIDI_BUTTON_WIDTH = 325;
    inline constexpr int GENERATE_MIDI_BUTTON_HEIGHT = 50;
    inline constexpr int PAUSE_BUTTON_X = 965;
    inline constexpr int PAUSE_BUTTON_Y = 320;
    inline constexpr int PAUSE_BUTTON_WIDTH = 160;
    inline constexpr int PAUSE_BUTTON_HEIGHT = 50;
    inline constexpr float BUTTON_ROUDING = 400.0f;

}