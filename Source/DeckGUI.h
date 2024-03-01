#pragma once
#include "DJAudioPlayer.h"

class DeckGUI : public juce::Component {
public:
    DeckGUI();
    ~DeckGUI();

    void paint(juce::Graphics &g) override;
    void resized() override;

private:
    TextButton playButton{"Play"};
    TextButton stopButton{"Stop"};
    TextButton loadButton{"Load"};
    Slider volSlider;
    Slider speedSlider;
    Slider positionSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};