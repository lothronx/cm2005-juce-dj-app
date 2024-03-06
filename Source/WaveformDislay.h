/*
  ==============================================================================

    WaveformDislay.h
    Created: 6 Mar 2024 3:28:54pm
    Author:  Yue Wu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDislay  : public juce::Component
{
public:
    WaveformDislay();
    ~WaveformDislay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDislay)
};
