#include "SpeedSlider.h"

//==============================================================================
SpeedSlider::SpeedSlider(DJAudioPlayer *_player) : player{_player} {
    speedLabel.setJustificationType(Justification::centred);
    speedSlider.setNormalisableRange(NormalisableRange<double>(-50, 50, 1));
    speedSlider.setValue(0.0);
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    speedSlider.setTextValueSuffix(" %");

    addAndMakeVisible(speedLabel);
    addAndMakeVisible(speedSlider);

    speedSlider.addListener(this);
}

SpeedSlider::~SpeedSlider() {
}

void SpeedSlider::paint(juce::Graphics &g) {
    g.setColour(Colours::grey.withAlpha(0.5f));
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15, 1);
}

void SpeedSlider::resized() {
    speedLabel.setBounds(0, 0, getWidth(), 25);
    speedSlider.setBounds(0, 25,getWidth(), getHeight()-40);
}

void SpeedSlider::sliderValueChanged(juce::Slider *slider) {
    player->setSpeed(slider->getValue());
}