#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class Knobs : public juce::Component,
              public juce::Slider::Listener {
public:
    explicit Knobs(DJAudioPlayer *player);

    ~Knobs() override;

    void paint(juce::Graphics &) override;

    void resized() override;

    void sliderValueChanged(juce::Slider *slider) override;

private:
    DJAudioPlayer *player;

    Label volLabel{"Volume", "Volume"};
    Slider volSlider;

    Label highLabel{"EQ High", "High"};
    Slider highSlider;

    Label midLabel{"EQ Mid", "Mid"};
    Slider midSlider;

    Label lowLabel{"EQ Low", "Low"};
    Slider lowSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knobs)
};
