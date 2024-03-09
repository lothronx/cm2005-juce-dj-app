/////////////////////// I wrote the following code //////////////////////

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/** SpeedSlider is a GUI component that allows the user to control the speed of a DJAudioPlayer audio source.*/
class SpeedSlider : public juce::Component,
                    public juce::Slider::Listener {

public:
    //==============================================================================
    /** Creates a speed slider to control the speed of a DJAudioPlayer audio source.
        @param player the DJAudioPlayer to control
    */
    explicit SpeedSlider(DJAudioPlayer *player);

    //==============================================================================
    /** Draws a rounded rectangle around the component to define its bounds. */
    void paint(juce::Graphics &) override;

    /** Positions the label and the slider within the component. */
    void resized() override;

    //==============================================================================
    /** Changes the speed of the audio source when the slider value changes. */
    void sliderValueChanged(juce::Slider *slider) override;

private:
    //==============================================================================
    // The audio source
    DJAudioPlayer *player;

    // The GUI subcomponents
    Label speedLabel{"Speed", "Speed"};
    Slider speedSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpeedSlider)
};

//////////////////////////// End of my code ////////////////////////////