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

public:
    TextInterpreter(MusicContext& ctx);

    void loadText(const std::string& input);
    void interpret();

    const std::vector<Voice>& getVoices() const;
    void clearVoices();
};