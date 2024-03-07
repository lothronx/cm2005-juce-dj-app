#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class VUMeter : public juce::Component, public juce::Timer {
public:
    VUMeter(DJAudioPlayer *_player, const Colour &_colour);

    ~VUMeter() override;

    void paint(juce::Graphics &) override;

    void resized() override;

    void timerCallback() override;

private:
    DJAudioPlayer *player;

    Colour colour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VUMeter)
};
