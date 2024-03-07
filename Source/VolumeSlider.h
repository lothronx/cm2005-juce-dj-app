#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class VolumeSlider : public juce::Component,
                     public juce::Slider::Listener,
                     public juce::ChangeListener{
public:
    explicit VolumeSlider(DJAudioPlayer *player);

    void paint(juce::Graphics &) override;

    void resized() override;

    void sliderValueChanged(juce::Slider *slider) override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    DJAudioPlayer *player;

    Label volLabel{"Volume", "Volume"};
    Slider volSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeSlider)
};
