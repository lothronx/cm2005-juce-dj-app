/////////////////////// I wrote the following code //////////////////////

#include "VUMeter.h"

//==============================================================================
VUMeter::VUMeter(DJAudioPlayer *_player, const Colour &_colour)
        : player{_player}
        , colour{_colour} {
    // To monitor the player's state
    player->addChangeListener(this);
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
    // RMS ranges from -100dB to 0dB.
    // For display purposes, we need to map it to the range from 0% to 100%
    float level = (100 + RMS) / 100;
    // Draw the level bar from the bottom up
    g.fillRect(0, getHeight(), getWidth(), static_cast<int>(-getHeight() * level));

}

void VUMeter::resized() {}

//==============================================================================
void VUMeter::changeListenerCallback(juce::ChangeBroadcaster *source) {
    if (source == player) {
        if (player->isPlaying()) {
            startTimer(1000 / 60);
        } else {
            stopTimer();
            // After stopping the timer, the timerCallback() function will no longer be called,
            // the RMS will not be updated, and the VU meter will remain it its last level
            // Thus, we need to manually reset the RMS value to silence and repaint the VU meter once
            RMS = -100.0f;
            repaint();
        }
    }
}

void VUMeter::timerCallback() {
    RMS = player->getRMSInDb();
    repaint();
}

//////////////////////////// End of my code ////////////////////////////
