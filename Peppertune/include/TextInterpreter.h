// Arquivo de interface do TextInterpreter
#pragma once

#include <string>
#include <vector>
#include "MusicContext.h"
#include "Voice.h"

class TextInterpreter {
private:
    MusicContext& context;
    std::string text;
    std::vector<Voice> voices;

    std::vector<std::string> splitLines(const std::string& input) const;
    bool isLineEmpty(const std::string& line) const;
    void processVoiceLine(const std::string& line, int voiceIndex);

public:
    TextInterpreter(MusicContext& ctx);

    void loadText(const std::string& input);
    void interpret();

    const std::vector<Voice>& getVoices() const;
    std::vector<std::vector<VoiceEvent>> getVoiceEvents() const;
    void clearVoices();
};