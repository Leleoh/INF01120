//Interface para vozes

#pragma once
#include <string>
#include "MusicContext.h"

class Voice {
private:
    int voiceId;

public:
    Voice(int id = 0);
    int getVoiceId() const;
    
    //Vai se implementado no passo 2
    void processLine(const std::string& line, MusicContext& ctx);
};