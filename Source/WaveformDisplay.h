#pragma once

#include <JuceHeader.h>

class WaveformDisplay : public juce::Component {
public:
    WaveformDisplay();

    void paint(juce::Graphics &g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};