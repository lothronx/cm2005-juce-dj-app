#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class JogWheel : public juce::Component, public juce::Timer {
public:
    explicit JogWheel(const Colour &colour);

    ~JogWheel() override;

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

    void drawWheel(juce::Graphics &g, const float centreX, const float centreY);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JogWheel)
};
