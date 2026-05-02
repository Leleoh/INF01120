// Peppertune/tests/test.cpp
//Arquivo vazio
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "MusicContext.h"
#include "TextInterpreter.h"
#include "Voice.h"

void testLinhaSimplesSemDelay() {
    MusicContext ctx(0);
    Voice voice(0);

    voice.processLine("CDE", ctx);
    const auto& events = voice.getEvents();

    assert(events.size() == 3);

    assert(events[0].type == VoiceEventType::Note);
    assert(events[0].pitch == "C6");
    assert(events[0].beat == 0);

    assert(events[1].type == VoiceEventType::Note);
    assert(events[1].pitch == "D6");
    assert(events[1].beat == 1);

    assert(events[2].type == VoiceEventType::Note);
    assert(events[2].pitch == "E6");
    assert(events[2].beat == 2);
}

void testLinhaComDelay() {
    MusicContext ctx(0);
    Voice voice(0);

    voice.processLine("[4] CDE", ctx);
    const auto& events = voice.getEvents();

    assert(events.size() == 7);

    for (int i = 0; i < 4; ++i) {
        assert(events[i].type == VoiceEventType::Rest);
        assert(events[i].beat == i);
    }

    assert(events[4].type == VoiceEventType::Note);
    assert(events[4].pitch == "C6");
    assert(events[4].beat == 4);

    assert(events[5].type == VoiceEventType::Note);
    assert(events[5].pitch == "D6");
    assert(events[5].beat == 5);

    assert(events[6].type == VoiceEventType::Note);
    assert(events[6].pitch == "E6");
    assert(events[6].beat == 6);
}

void testMudancaDeOitava() {
    MusicContext ctx(0);
    Voice voice(0);

    voice.processLine("C?DVE", ctx);
    const auto& events = voice.getEvents();

    assert(events.size() == 5);

    assert(events[0].type == VoiceEventType::Note);
    assert(events[0].pitch == "C6");

    assert(events[1].type == VoiceEventType::OctaveChange);
    assert(events[1].octave == 7);

    assert(events[2].type == VoiceEventType::Note);
    assert(events[2].pitch == "D7");

    assert(events[3].type == VoiceEventType::OctaveChange);
    assert(events[3].octave == 6);

    assert(events[4].type == VoiceEventType::Note);
    assert(events[4].pitch == "E6");
}

void testEspacoDobrandoVolume() {
    MusicContext ctx(0);
    Voice voice(0);

    voice.processLine("C D", ctx);
    const auto& events = voice.getEvents();

    assert(events.size() == 3);

    assert(events[0].type == VoiceEventType::Note);
    assert(events[0].volume == 100);

    assert(events[1].type == VoiceEventType::VolumeChange);
    assert(events[1].volume == 127);

    assert(events[2].type == VoiceEventType::Note);
    assert(events[2].pitch == "D6");
    assert(events[2].volume == 127);
}

void testTrocaDeInstrumento() {
    MusicContext ctx(0);
    Voice voice(0);

    voice.processLine("C!D", ctx);
    const auto& events = voice.getEvents();

    assert(events.size() == 3);

    assert(events[0].type == VoiceEventType::Note);
    assert(events[0].instrument == 6);

    assert(events[1].type == VoiceEventType::InstrumentChange);
    assert(events[1].instrument == 22);

    assert(events[2].type == VoiceEventType::Note);
    assert(events[2].pitch == "D6");
    assert(events[2].instrument == 22);
}

#include <fstream>
void testDuasLinhasDuasVozes() {
    std::ofstream out("test_temp.txt");
    out << "CDE\nGAB\n";
    out.close();

    TextInterpreter interpreter;
    interpreter.parseFile("test_temp.txt");

    const auto& voices = interpreter.getVoices();

    assert(voices.size() == 2);

    assert(voices[0].getVoiceID() == 0);
    assert(voices[1].getVoiceID() == 1);

    const auto& allEvents = interpreter.getAllVoiceEvents();

    assert(allEvents.size() == 2);

    const auto& events0 = allEvents[0];
    const auto& events1 = allEvents[1];

    assert(events0.size() == 3);
    assert(events1.size() == 3);

    assert(events0[0].pitch == "C6");
    assert(events1[0].pitch == "G5");
}

int main() {
    testLinhaSimplesSemDelay();
    std::cout << "[OK] testLinhaSimplesSemDelay\n";

    testLinhaComDelay();
    std::cout << "[OK] testLinhaComDelay\n";

    testMudancaDeOitava();
    std::cout << "[OK] testMudancaDeOitava\n";

    testEspacoDobrandoVolume();
    std::cout << "[OK] testEspacoDobrandoVolume\n";

    testTrocaDeInstrumento();
    std::cout << "[OK] testTrocaDeInstrumento\n";

    testDuasLinhasDuasVozes();
    std::cout << "[OK] testDuasLinhasDuasVozes\n";

    std::cout << "\nTodos os testes passaram.\n";
    return 0;
}