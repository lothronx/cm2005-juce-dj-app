#include "Knobs.h"

//==============================================================================
Knobs::Knobs(DJAudioPlayer *_player) : player{_player} {

    volLabel.setJustificationType(Justification::centred);
    volLabel.attachToComponent(&volSlider, false);
    volSlider.setRange(0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setDoubleClickReturnValue(true, 0.5);
    volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    highLabel.setJustificationType(Justification::centred);
    highLabel.attachToComponent(&highSlider, false);
    highSlider.setRange(-24.0, 24.0);
    highSlider.setValue(0);
    highSlider.setDoubleClickReturnValue(true, 0);
    highSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    highSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    midLabel.setJustificationType(Justification::centred);
    midLabel.attachToComponent(&midSlider, false);
    midSlider.setRange(-24.0, 24.0);
    midSlider.setValue(0);
    midSlider.setDoubleClickReturnValue(true, 0);
    midSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    midSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    lowLabel.setJustificationType(Justification::centred);
    lowLabel.attachToComponent(&lowSlider, false);
    lowSlider.setRange(-24.0, 24.0);
    lowSlider.setValue(0);
    lowSlider.setDoubleClickReturnValue(true, 0);
    lowSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    lowSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(volLabel);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(highLabel);
    addAndMakeVisible(highSlider);
    addAndMakeVisible(midLabel);
    addAndMakeVisible(midSlider);
    addAndMakeVisible(lowLabel);
    addAndMakeVisible(lowSlider);

    player->addChangeListener(this);
    volSlider.addListener(this);
    highSlider.addListener(this);
    midSlider.addListener(this);
    lowSlider.addListener(this);
}

void Knobs::paint(juce::Graphics &g) {

}

void Knobs::resized() {
    auto h = getHeight();
    auto w = getWidth();

    volLabel.setBounds(0, 0, w, h * 2/40);
    volSlider.setBounds( 0, h * 3/40, w, h * 7/40);
    highLabel.setBounds(0, h * 10/40, w, h * 2/40);
    highSlider.setBounds( 0, h * 13/40, w, h * 7/40);
    midLabel.setBounds(0, h * 20/40, w, h * 2/40);
    midSlider.setBounds(0, h * 23/40, w, h * 7/40);
    lowLabel.setBounds(0, h * 30/40, w, h * 2/40);
    lowSlider.setBounds(0, h * 33/40, w, h * 7/40);

}

void Knobs::sliderValueChanged(juce::Slider *slider) {
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    if (slider == &highSlider) {
        player->setHighEQ(static_cast<float>(slider->getValue()));
    }
    if (slider == &midSlider) {
        player->setMidEQ(static_cast<float>(slider->getValue()));
    }
    if (slider == &lowSlider) {
        player->setLowEQ(static_cast<float>(slider->getValue()));
    }
}

void Knobs::changeListenerCallback(juce::ChangeBroadcaster *source) {
    if (source == player) {
        volSlider.setValue(player->getGain());
    }
}