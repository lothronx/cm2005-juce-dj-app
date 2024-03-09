/////////////////////// I wrote the following code //////////////////////

#include "SpeedSlider.h"

//==============================================================================
SpeedSlider::SpeedSlider(DJAudioPlayer *_player)
        : player{_player} {
    // Initialize the speed slider
    // The speed slider is a vertical linear slider with a label above and an editable text box below
    // The initial value is 0%. The range is -50% to 50%, with a step of 1%
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setNormalisableRange(NormalisableRange<double>(-50, 50, 1));
    speedSlider.setValue(0.0);
    speedLabel.setJustificationType(Justification::centred);
    speedLabel.attachToComponent(&speedSlider, false);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    speedSlider.setTextValueSuffix(" %");

    addAndMakeVisible(speedLabel);
    addAndMakeVisible(speedSlider);

    speedSlider.addListener(this);
}

//==============================================================================
void SpeedSlider::paint(juce::Graphics &g) {
    // Draw a rounded rectangle around the component to define its bounds
    g.setColour(Colours::grey.withAlpha(0.5f));
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15, 1);
}

void SpeedSlider::resized() {
    // Position the label on top and the slider below
    speedLabel.setBounds(0, 0, getWidth(), 25);
    speedSlider.setBounds(0, 25, getWidth(), getHeight() - 40);
}

//==============================================================================
void SpeedSlider::sliderValueChanged(juce::Slider *slider) {
    player->setSpeed(slider->getValue());
}

//////////////////////////// End of my code ////////////////////////////