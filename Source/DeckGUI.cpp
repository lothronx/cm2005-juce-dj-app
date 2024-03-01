#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* _player) : player{_player}{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);

    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    speedSlider.setRange(0.0, 10.0);
    speedSlider.setValue(1.0);
    positionSlider.setRange(0.0, 1.0);
    positionSlider.setValue(0.0);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    positionSlider.addListener(this);
}

void DeckGUI::paint(Graphics &g) {
    Component::paint(g);
}

void DeckGUI::resized() {
    auto h = getHeight() / 6;
    loadButton.setBounds(getWidth() / 2 - 50, 0, 100, 100);
    playButton.setBounds(getWidth() / 2 - 50, h, 100, 100);
    stopButton.setBounds(getWidth() / 2 - 50, h * 2, 100, 100);
    volSlider.setBounds(getWidth() / 4, h * 3, getWidth() / 2, 100);
    speedSlider.setBounds(getWidth() / 4, h * 4, getWidth() / 2, 100);
    positionSlider.setBounds(getWidth() / 4, h * 5, getWidth() / 2, 100);
}

void DeckGUI::buttonClicked(juce::Button *button) {
    if (button == &playButton) {
        player->start();
    }
    if (button == &stopButton) {
        player->stop();
    }
    if (button == &loadButton) {
        fChooser.launchAsync(FileBrowserComponent::canSelectFiles, [this](const FileChooser &chooser) {
            player->loadURL(URL{chooser.getResult()});
        });
    }
}

void DeckGUI::sliderValueChanged(juce::Slider *slider) {
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider) {
        player->setSpeed(slider->getValue());
    }
    if (slider == &positionSlider) {
        player->setPosition(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const StringArray &files) {
    return true;
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y) {
    player->loadURL(URL{File{files[0]}});
}
