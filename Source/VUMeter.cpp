#include "VUMeter.h"

VUMeter::VUMeter(DJAudioPlayer *_player, const Colour &_colour)
        : player{_player}, colour{_colour} {
    startTimer(1000/60);
}

VUMeter::~VUMeter() {
    stopTimer();
}

void VUMeter::paint(juce::Graphics &g) {
    g.fillAll(Colours::darkgrey);

    g.setColour(colour);

    if(player->isPlaying()){
        float level = (100 + player->getRMS()) / 100;
        g.fillRect(0, getHeight(), getWidth(), static_cast<int>(-getHeight() * level));
    }
}

void VUMeter::resized() {}

void VUMeter::timerCallback() {
    repaint();
}