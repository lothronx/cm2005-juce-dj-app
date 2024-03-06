#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class JogWheel : public juce::Component, public juce::Timer, public juce::ChangeListener {
public:
    JogWheel(DJAudioPlayer *player, const Colour &colour);

    ~JogWheel() override;

    void paint(juce::Graphics &) override;

    void resized() override;

    void timerCallback() override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    DJAudioPlayer *player;

    Colour colour;

    bool isPlaying{false};

    float rotationAngle{0.0f};
    const float rotationSpeed{0.03f};

    void drawWheel(juce::Graphics &g, const float centreX, const float centreY);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JogWheel)
};
