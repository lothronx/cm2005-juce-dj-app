/////////////////////// I wrote the following code //////////////////////

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/** VUMeter is a GUI component that displays the real-time volume of a DJAudioPlayer audio source. */
class VUMeter :
        public juce::Component,
        public juce::Timer,
        public juce::ChangeListener {
public:
    //==============================================================================
    /** Creates a VU (volume unit) meter to display the real-time volume of a given DJAudioPlayer audio source.
     * @param _player the audio source to display
     * @param _colour the colour of the VU meter
     */
    VUMeter(DJAudioPlayer *_player, const Colour &_colour);

    /** Destructor. */
    ~VUMeter() override;

    //==============================================================================
    /** Draws the VU meter. */
    void paint(juce::Graphics &) override;

    /** Implementation of the Component method. */
    void resized() override;

    //==============================================================================
    /** Starts or stops the timer when the state of the player changes. */
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    /** Repaints the VU meter. */
    void timerCallback() override;

private:
    //==============================================================================
    DJAudioPlayer *player;

    Colour colour;

    // RMS is the average loudness of the current audio block, it ranges from -100dB to 0dB
    // The initial value is -100dB, which means silence
    float RMS{-100.0f};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VUMeter)
};

//////////////////////////// End of my code ////////////////////////////