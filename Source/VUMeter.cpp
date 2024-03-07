#include "VUMeter.h"

VUMeter::VUMeter(DJAudioPlayer *_player, const Colour &_colour)
        : player{_player}, colour{_colour} {
    startTimer(1000 / 60);
}

VUMeter::~VUMeter() {
    stopTimer();
}

void VUMeter::paint(juce::Graphics &g) {

    auto gradient = juce::ColourGradient::vertical(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId), 0, Colours::darkgrey, static_cast<float>(getHeight()));
    g.setGradientFill(gradient);
    g.fillRect(0, 0, getWidth(), getHeight());

    g.setColour(Colours::darkgrey);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(colour);
    if (player->isPlaying()) {
        float level = (100 + player->getRMS()) / 100;
        g.fillRect(0, getHeight(), getWidth(), static_cast<int>(static_cast<float>(-getHeight()) * level));
    }
}

void VUMeter::resized() {}

void VUMeter::timerCallback() {
    repaint();
}