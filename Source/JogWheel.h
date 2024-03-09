/////////////////////// I wrote the following code //////////////////////

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/** JogWheel is a GUI components that displays a vinyl record that rotates when the DJAudioPlayer is playing. */
class JogWheel : public juce::Component,
                 public juce::Timer,
                 public juce::ChangeListener {
public:
    //==============================================================================
    /** Creates a jog wheel to display the playback state of a DJAudioPlayer.
     * @param player The DJAudioPlayer to monitor for changes in playback state.
     * @param colour The colour of the jog wheel.
     * */
    JogWheel(DJAudioPlayer *player, const Colour &colour);

    /** Destructor. */
    ~JogWheel() override;

    //==============================================================================
    /** Rotate the canvas and draw the jog wheel. */
    void paint(juce::Graphics &) override;

    /** Implementation of the Component method. */
    void resized() override;

    //==============================================================================
    /** Starts or stops then timer when the state of the player changes. */
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    /** Keeps changing the rotation angle and repainting the jog wheel. */
    void timerCallback() override;

private:
    //==============================================================================
    // The DJAudioPlayer to monitor for changes in playback state
    DJAudioPlayer *player;

    // The colour of the jog wheel
    Colour colour;

    // The rotation speed and the rotation angle calculated from the speed
    float rotationAngle{0.0f};
    const float rotationSpeed{0.03f};

    /** Draws the jog wheel.
     * @param centreX The x-coordinate of the centre of the jog wheel.
     * @param centreY The y-coordinate of the centre of the jog wheel.
     * */
    void drawWheel(juce::Graphics &g, float centreX, float centreY);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JogWheel)
};

//////////////////////////// End of my code ////////////////////////////