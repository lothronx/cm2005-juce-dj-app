#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SpinningDisc : public juce::Component, public juce::Timer {
public:
    explicit SpinningDisc(const Colour &colour);

    ~SpinningDisc() override;

    void paint(juce::Graphics &) override;

    void resized() override;

    void timerCallback() override;

    void setPlaying(bool shouldBePlaying);

private:

    Colour colour;

    bool isPlaying{false};

    float rotationAngle{0.0f};
    const float rotationSpeed{0.03f};
    const float fastForwardSpeed{0.1f};
    const float fastRewindSpeed{-0.1f};

    void drawDisc(juce::Graphics &g, const float centreX, const float centreY);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpinningDisc)
};
