//Arquivo de interface do TextInterpreter
#ifndef TEXTINTERPRETER_H
#define TEXTINTERPRETER_H

#include <string>
#include <vector>
#include "MusicContext.h"
#include "Voice.h"

class TextInterpreter{
    private:

    int globalBPM;
    int customOctave;
    int customVolume;

    //Array dinâmico que guarda as vozes (linhas)
    std::vector<MusicContext> voices;
    
    //Armazena os eventos processados pela lógica do MidiGenerator
    std::vector<std::vector<VoiceEvent>> allVoiceEvents;

    public:
    TextInterpreter();

    // Setters para customização via UI
    void setInitialBPM(int bpm);
    void setInitialOctave(int octave);
    void setInitialVolume(int volume);

    //Função que lê o texto diretamente de uma string (na memória)
    void parseString(const std::string& text);

    //Getters para gerar áudio
    int getGlobalBPM() const;
    std::vector<MusicContext> getVoices() const;
    std::vector<std::vector<VoiceEvent>> getAllVoiceEvents() const;

};

#endif