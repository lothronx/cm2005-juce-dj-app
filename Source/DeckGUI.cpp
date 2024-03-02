#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse)
        : player{_player}, waveformDisplay{formatManagerToUse, cacheToUse} {
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(waveformDisplay);

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

    startTimer(100);
}


DeckGUI::~DeckGUI() {
    stopTimer();
}

void DeckGUI::paint(Graphics &g) {
    Component::paint(g);
}

void DeckGUI::resized() {
    auto h = getHeight() / 8;
    loadButton.setBounds(0, 0, getWidth(), h);
    playButton.setBounds(0, h, getWidth(), h);
    stopButton.setBounds(0, h * 2, getWidth(), h);
    volSlider.setBounds(0, h * 3, getWidth(), h);
    speedSlider.setBounds(0, h * 4, getWidth(), h);
    positionSlider.setBounds(0, h * 5, getWidth(), h);
    waveformDisplay.setBounds(0, h * 6, getWidth(), h * 2);
}

void DeckGUI::buttonClicked(juce::Button *button) {
    if (button == &playButton) {
        player->start();
    }
    if (button == &stopButton) {
        player->stop();
    }
    if (button == &loadButton) {
        fChooser.launchAsync(FileBrowserComponent::canSelectFiles,
                             [this](const FileChooser &chooser) {
            player->loadURL(URL{chooser.getResult()});
            waveformDisplay.loadURL(URL{chooser.getResult()});
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
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const StringArray &files) {
    return true;
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y) {
    player->loadURL(URL{File{files[0]}});
}

void DeckGUI::timerCallback() {
    positionSlider.setValue(player->getPositionRelative(), dontSendNotification);
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

