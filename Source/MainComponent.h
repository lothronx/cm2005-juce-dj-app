#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent,
                      public juce::Button::Listener,
                      public juce::Slider::Listener {
public:
    //==============================================================================
    MainComponent();

    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

    void releaseResources() override;

    //==============================================================================
    void paint(juce::Graphics &g) override;

    void resized() override;

    //==============================================================================
    void buttonClicked(juce::Button *button) override;

    void sliderValueChanged(juce::Slider *slider) override;

private:
    //==============================================================================
    // Your private member variables go here...
    TextButton playButton{"Play"};
    TextButton stopButton{"Stop"};
    TextButton loadButton{"Load"};
    Slider volSlider;
    Slider speedSlider;
    Slider positionSlider;
    juce::FileChooser fChooser{"Select a file..."};
    DJAudioPlayer player1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
