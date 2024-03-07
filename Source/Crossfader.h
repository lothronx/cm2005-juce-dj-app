#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/*
*/
class Crossfader : public juce::Component,
                   public ::Slider::Listener {
public:
    Crossfader(DJAudioPlayer *player1, DJAudioPlayer *player2, juce::Colour color1, juce::Colour color2);

    ~Crossfader() override;

    void paint(juce::Graphics &) override;

    void resized() override;

    void sliderValueChanged(juce::Slider *slider) override;

private:
    DJAudioPlayer *player1, *player2;

    CustomLookAndFeel customLookAndFeel;

    Slider crossfaderSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Crossfader)
};
