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

        // Roda a lógica da funcionalidade do colega
        Voice friendVoice(voiceID);
        
        // Aplica os valores da UI caso tenham sido configurados
        if (customOctave != -1) {
            friendVoice.setBaseOctave(customOctave);
            friendVoice.setCurrentOctave(customOctave);
        }
        if (customVolume != -1) {
            friendVoice.setBaseVolume(customVolume);
            friendVoice.setCurrentVolume(customVolume);
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