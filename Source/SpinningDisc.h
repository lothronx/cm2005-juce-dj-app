#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SpinningDisc : public juce::Component {
public:
    SpinningDisc();

    ~SpinningDisc() override;

    void paint(juce::Graphics &) override;

    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpinningDisc)
};
