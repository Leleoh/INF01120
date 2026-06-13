//Arquivo inicial de lógica de interpretação de texto

#include "TextInterpreter.h"
#include "MusicTranslator.h"
#include <fstream>
#include <iostream>
#include "Constants.h"
#include <sstream>

TextInterpreter::TextInterpreter(){
    globalBPM = Peppertune::Constants::DEFAULT_BPM; //Garante que começa com 120
    customOctave = -1;
    customVolume = -1;
}

void TextInterpreter::setInitialBPM(int bpm) { globalBPM = bpm; }
void TextInterpreter::setInitialOctave(int octave) { customOctave = octave; }
void TextInterpreter::setInitialVolume(int vol) { customVolume = vol; }


void TextInterpreter::parseString(const std::string& text){
    std::istringstream stream(text);
    std::string currentLine;
    int voiceID = 0;

    //Analisa o texto até achar um \n, vai jogando dentro do currentLine
    while (std::getline(stream, currentLine)){

        //Instancia uma nova voz
        MusicContext newVoice(voiceID);
        newVoice.setBpm(globalBPM);

        Voice friendVoice(voiceID);
        
        //aplica os valores da UI como BASE para a primeira voz, e defasa as demais
        //oitavas
        if (customOctave != -1) {
            int calcOctave = customOctave - (voiceID % 4);
            if (calcOctave < 0) calcOctave = 0;
            friendVoice.setBaseOctave(calcOctave);
            friendVoice.setCurrentOctave(calcOctave);
        }
        //mesma coisa para o volume
        if (customVolume != -1) {
            int calcVolume = customVolume - (voiceID % 4) * 20;
            if (calcVolume < 0) calcVolume = 0;
            friendVoice.setBaseVolume(calcVolume);
            friendVoice.setCurrentVolume(calcVolume);
        }

        friendVoice.processLine(currentLine, newVoice);
        //Chama o tradutor para aplicar a função definida do mapeamento
        for (char letter: currentLine){
            MusicTranslator::applyMapping(letter, newVoice, globalBPM);
        }

        allVoiceEvents.push_back(friendVoice.getEvents());
        voices.push_back(newVoice);

        voiceID++;
    }
}

int TextInterpreter::getGlobalBPM() const{
    return globalBPM;
}

std::vector<MusicContext> TextInterpreter::getVoices() const{
    return voices;
}

std::vector<std::vector<VoiceEvent>> TextInterpreter::getAllVoiceEvents() const{
    return allVoiceEvents;
}