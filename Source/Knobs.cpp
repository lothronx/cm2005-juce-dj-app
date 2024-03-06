#include "Knobs.h"

//==============================================================================
Knobs::Knobs(DJAudioPlayer *_player) : player{_player} {

    volLabel.setJustificationType(Justification::centred);
    volLabel.attachToComponent(&volSlider, false);
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setDoubleClickReturnValue(true, 0.5);
    volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    highLabel.setJustificationType(Justification::centred);
    highLabel.attachToComponent(&highSlider, false);
    highSlider.setRange(0.0, 1.0);
    highSlider.setValue(0.5);
    highSlider.setDoubleClickReturnValue(true, 0.5);
    highSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    highSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    midLabel.setJustificationType(Justification::centred);
    midLabel.attachToComponent(&midSlider, false);
    midSlider.setRange(0.0, 1.0);
    midSlider.setValue(0.5);
    midSlider.setDoubleClickReturnValue(true, 0.5);
    midSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    midSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    lowLabel.setJustificationType(Justification::centred);
    lowLabel.attachToComponent(&lowSlider, false);
    lowSlider.setRange(0.0, 1.0);
    lowSlider.setValue(0.5);
    lowSlider.setDoubleClickReturnValue(true, 0.5);
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

    volSlider.addListener(this);
    highSlider.addListener(this);
    midSlider.addListener(this);
    lowSlider.addListener(this);
}

Knobs::~Knobs() {
}

void Knobs::paint(juce::Graphics &g) {

}

void Knobs::resized() {
    auto h = getHeight() / 40;
    auto w = getWidth();

    volLabel.setBounds(0, 0, w, h * 2);
    volSlider.setBounds(w * 0, h * 3, w, h * 7);
    highLabel.setBounds(0, h * 10, w, h * 2);
    highSlider.setBounds(w * 0, h * 13, w, h * 7);
    midLabel.setBounds(0, h * 20, w, h * 2);
    midSlider.setBounds(w * 0, h * 23, w, h * 7);
    lowLabel.setBounds(0, h * 30, w, h * 2);
    lowSlider.setBounds(w * 0, h * 33, w, h * 7);
}

void Knobs::sliderValueChanged(juce::Slider *slider) {
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    if (slider == &highSlider) {
        player->setHighGain(slider->getValue());
    }
    if (slider == &midSlider) {
        player->setMidGain(slider->getValue());
    }
    if (slider == &lowSlider) {
        player->setLowGain(slider->getValue());
    }
}