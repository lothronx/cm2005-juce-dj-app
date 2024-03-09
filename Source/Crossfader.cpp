/////////////////////// I wrote the following code //////////////////////

#include "Crossfader.h"

Crossfader::Crossfader(DJAudioPlayer *_player1,
                       DJAudioPlayer *_player2,
                       juce::Colour color1,
                       juce::Colour color2)
        : player1{_player1}
        , player2{_player2}
        , customLookAndFeel{color1, color2}{

    // Set the custom look and feel
    setLookAndFeel(&customLookAndFeel);

    // Initialize the crossfader label and slider
    // The slider ranges from 0 to 1 with a default value of 0.5
    crossfaderLabel.setJustificationType(Justification::centred);
    crossfaderSlider.setRange(0, 1);
    crossfaderSlider.setValue(0.5);
    crossfaderSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    crossfaderSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(crossfaderLabel);
    addAndMakeVisible(crossfaderSlider);

    crossfaderSlider.addListener(this);
}

Crossfader::~Crossfader() {
    setLookAndFeel(nullptr);
}

void Crossfader::paint(juce::Graphics &g) {}

void Crossfader::resized() {
    crossfaderSlider.setBounds(0, 0, getWidth(), getHeight());
    crossfaderLabel.setBounds(0, getHeight()*4/5, getWidth(), getHeight()/5-10);
}

void Crossfader::sliderValueChanged(juce::Slider *slider) {
    // Because the slider thumb is on player 1's side when the value is 0,
    // thus 0 means 100% player 1 and 0% player 2.
    // Similarly, 1 means 0% player 1 and 100% player 2.
    player1->setGain((1 - slider->getValue()));
    player2->setGain(slider->getValue());
}

//////////////////////////// End of my code ////////////////////////////