/////////////////////// I wrote the following code //////////////////////

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/** Knobs is a GUI component that contains 4 rotary sliders.
 * It allows the user to change the volume and the high, mid, and low EQ of a DJAudioPlayer audio source.
 */
class Knobs : public juce::Component,
              public juce::Slider::Listener,
              public juce::ChangeListener {
public:
    //==============================================================================
    /** Creates a Knobs component that contains 4 knobs to control the volume and EQ of a DJAudioPlayer audio source.
     * @param player the DJAudioPlayer audio source to control
     */
    explicit Knobs(DJAudioPlayer *player);

    //==============================================================================
    /** Implementation of the Component method. */
    void paint(juce::Graphics &) override;

    /** Positions and sizes the 4 knobs. */
    void resized() override;

    //==============================================================================
    /** Changes the volume and EQ of the audio source when the corresponding slider value changes. */
    void sliderValueChanged(juce::Slider *slider) override;

    /** Updates the volume slider value when the volume of the audio source is changed by the crossfader. */
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    //==============================================================================
    // The DJAudioPlayer audio source to control
    DJAudioPlayer *player;

    // The subcomponents
    Label volLabel{"Volume", "Volume"};
    Slider volSlider;

    Label highLabel{"EQ High", "High"};
    Slider highSlider;

    Label midLabel{"EQ Mid", "Mid"};
    Slider midSlider;

    Label lowLabel{"EQ Low", "Low"};
    Slider lowSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knobs)
};

//////////////////////////// End of my code ////////////////////////////