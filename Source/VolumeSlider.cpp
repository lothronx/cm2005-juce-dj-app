#include "VolumeSlider.h"

//==============================================================================
VolumeSlider::VolumeSlider(DJAudioPlayer *_player) : player{_player} {

    volLabel.setJustificationType(Justification::centred);
    volLabel.attachToComponent(&volSlider, false);
    volSlider.setRange(0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setDoubleClickReturnValue(true, 0.5);
    volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(volLabel);
    addAndMakeVisible(volSlider);

    player->addChangeListener(this);
    volSlider.addListener(this);
}

void VolumeSlider::paint(juce::Graphics &g) {

}

void VolumeSlider::resized() {
    auto h = getHeight() / 40;
    auto w = getWidth();

    volLabel.setBounds(0, 0, w, h * 2);
    volSlider.setBounds(w * 0, h * 3, w, h * 7);
}

void VolumeSlider::sliderValueChanged(juce::Slider *slider) {
        player->setGain(slider->getValue());
}

void VolumeSlider::changeListenerCallback(juce::ChangeBroadcaster *source) {
    if (source == player) {
        volSlider.setValue(player->getGain());
    }
}