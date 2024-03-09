/////////////////////// I wrote the following code //////////////////////

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "CustomLookAndFeel.h"

/** Crossfader is a GUI component that allows the user
 * to control the volume ratio of two DJAudioPlayer audio sources via a slider. */
class Crossfader : public juce::Component,
                   public ::Slider::Listener {
public:
    //==============================================================================
    /** Creates a crossfader that controls the volume ratio of two DJAudioPlayer audio sources.
     * @param player1 The first DJAudioPlayer to control
     * @param player2 The second DJAudioPlayer to control
     * @param color1 The color indicating the volume of the first DJAudioPlayer
     * @param color2 The color indicating the volume of the second DJAudioPlayer
     */
    Crossfader(DJAudioPlayer *player1,
               DJAudioPlayer *player2,
               juce::Colour color1,
               juce::Colour color2);

    /** Destructor */
    ~Crossfader() override;

    //==============================================================================
    /** Implementation of the Component method */
    void paint(juce::Graphics &) override;

    /** Positions and sizes the child components */
    void resized() override;

    //==============================================================================
    /** Updates the volume of both DJAudioPlayers when the slider is moved */
    void sliderValueChanged(juce::Slider *slider) override;

private:
    // The two DJAudioPlayers that the Crossfader controls
    DJAudioPlayer *player1, *player2;

    // The styling
    CustomLookAndFeel customLookAndFeel;

    // The subcomponents
    Label crossfaderLabel{"Crossfader", "Crossfader"};
    Slider crossfaderSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Crossfader)
};

//////////////////////////// End of my code ////////////////////////////
