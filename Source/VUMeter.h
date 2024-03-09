/////////////////////// I wrote the following code //////////////////////

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/** VUMeter is a GUI component that displays the real-time volume of a DJAudioPlayer audio source. */
class VUMeter :
        public juce::Component,
        public juce::Timer {
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

    /** Implements the Component method. */
    void resized() override;

    //==============================================================================
    /** Repaints the VU meter at a regular interval. */
    void timerCallback() override;

private:
    //==============================================================================
    DJAudioPlayer *player;

    Colour colour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VUMeter)
};

//////////////////////////// End of my code ////////////////////////////