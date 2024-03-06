#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class SpeedSlider : public juce::Component,
                    public juce::Slider::Listener {
public:
    explicit SpeedSlider(DJAudioPlayer *player);

    ~SpeedSlider() override;

    void paint(juce::Graphics &) override;

    void resized() override;

    void sliderValueChanged(juce::Slider *slider) override;

private:
    DJAudioPlayer *player;

    Label speedLabel{"Speed", "Speed"};
    Slider speedSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpeedSlider)
};
