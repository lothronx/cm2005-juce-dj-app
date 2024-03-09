/////////////////////// I wrote the following code //////////////////////

#include "VUMeter.h"

//==============================================================================
VUMeter::VUMeter(DJAudioPlayer *_player, const Colour &_colour)
        : player{_player}
        , colour{_colour} {
    startTimer(1000 / 60);
}

VUMeter::~VUMeter() {
    stopTimer();
}

//==============================================================================
void VUMeter::paint(juce::Graphics &g) {
    // The VU meter background
    auto gradient = juce::ColourGradient::vertical(
            getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
            0,
            Colours::darkgrey,
            static_cast<float>(getHeight()));
    g.setGradientFill(gradient);
    g.fillRect(0, 0, getWidth(), getHeight());

    // The VU meter outline
    g.setColour(Colours::darkgrey);
    g.drawRect(getLocalBounds(), 1);

    // The VU meter level as a coloured bar
    g.setColour(colour);
    if (player->isPlaying()) {
        // getRMSInDb() returns the current RMS in decibels.
        // RMS is the average loudness of the current audio block.
        // It ranges from -100 to 0.
        // For display purposes, we map it to level, which ranges from 0 to 1.
        float RMS = player->getRMSInDb();
        float level = (100 + RMS) / 100;
        // Draw the level bar from the bottom up
        g.fillRect(0, getHeight(), getWidth(), static_cast<int>(-getHeight() * level));
    }
}

void VUMeter::resized() {}

//==============================================================================
void VUMeter::timerCallback() {
    repaint();
}

//////////////////////////// End of my code ////////////////////////////
