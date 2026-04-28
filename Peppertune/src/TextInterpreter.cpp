// Arquivo inicial de lógica de interpretação de texto
#include "TextInterpreter.h"
#include <cctype>
#include <iostream>
#include <sstream>

TextInterpreter::TextInterpreter(MusicContext& ctx) : context(ctx) {}

void TextInterpreter::loadText(const std::string& input) {
    text = input;
    std::cout << "[TextInterpreter] Texto carregado (tamanho: "
              << text.size() << " chars)\n";
}

void TextInterpreter::clearVoices() {
    voices.clear();
}

const std::vector<Voice>& TextInterpreter::getVoices() const {
    return voices;
}

std::vector<std::vector<VoiceEvent>> TextInterpreter::getVoiceEvents() const {
    std::vector<std::vector<VoiceEvent>> allEvents;
    allEvents.reserve(voices.size());

    for (const auto& voice : voices) {
        allEvents.push_back(voice.getEvents());
    }

    return allEvents;
}

std::vector<std::string> TextInterpreter::splitLines(const std::string& input) const {
    std::vector<std::string> lines;
    std::istringstream stream(input);
    std::string line;

    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(line);
    }

    return lines;
}

bool TextInterpreter::isLineEmpty(const std::string& line) const {
    for (char c : line) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

void TextInterpreter::processVoiceLine(const std::string& line, int voiceIndex) {
    Voice voice(voiceIndex);
    voice.processLine(line, context);
    voices.push_back(voice);
}

void TextInterpreter::interpret() {
    clearVoices();

    std::vector<std::string> lines = splitLines(text);
    int voiceIndex = 0;

    for (const auto& line : lines) {
        if (isLineEmpty(line)) {
            continue;
        }

        processVoiceLine(line, voiceIndex);
        ++voiceIndex;
    }

    std::cout << "[TextInterpreter] Interpretacao concluida: "
              << voices.size() << " vozes processadas.\n";
}