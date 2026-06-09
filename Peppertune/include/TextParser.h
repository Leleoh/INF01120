#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Constants.h"

//parser que recebe o texto da interface e o processa para gerar as vozes (linhas) que serão interpretadas pelo TextInterpreter.
class TextParser {
private:
std::vector<std::string> voices;

public:
    TextParser();
    void Parse(const char* text);
    std::string GetVoice(int index);
};