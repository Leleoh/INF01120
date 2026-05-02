//Arquivo inicial de lógica de interpretação de texto

#include "TextInterpreter.h"
#include "MusicTranslator.h"
#include <fstream>
#include <iostream>
#include "Constants.h"

TextInterpreter::TextInterpreter(){
    globalBPM = Peppertune::Constants::DEFAULT_BPM; //Garante que começa com 120
}

void TextInterpreter::parseFile(const std::string& filepath){
    
    //Tenta abrir o arquiv .txt
    std::ifstream file(filepath);

    //Erro de abertura
    if (!file.is_open()){
        std::cerr << "Erro: Não foi possível abrir o arquivo " << filepath << std::endl;
        return;
    }

    std::string currentLine;
    int voiceID = 0;

    //Analisa o texto até achar um \n, vai jogando dentro do currentLine
    while (std::getline(file, currentLine)){

        //Instancia uma nova voz
        MusicContext newVoice(voiceID);

        // Roda a lógica da funcionalidade do colega
        Voice friendVoice(voiceID);
        friendVoice.processLine(currentLine, newVoice);

        //Chama o tradutor para aplicar a função definida do mapeamento
        for (char letter: currentLine){
            MusicTranslator::applyMapping(letter, newVoice, globalBPM);
        }

        allVoiceEvents.push_back(friendVoice.getEvents());
        voices.push_back(newVoice);

        voiceID++;
    }

    file.close();
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