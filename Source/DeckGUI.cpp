#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse)
        : player{_player}, waveformDisplay{formatManagerToUse, cacheToUse} {
    addAndMakeVisible(loopButton);
    addAndMakeVisible(playPauseButton);
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

    loopButton.addListener(this);
    playPauseButton.addListener(this);
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
    auto h = getHeight() / 10;
    auto w = getWidth() / 10;

    waveformDisplay.setBounds(0, 0, getWidth(), h * 2);

    loadButton.setBounds(w, h * 8, w * 2, h);
    playPauseButton.setBounds(w * 4, h * 8, w * 2, h);
    loopButton.setBounds(w * 7, h * 8, w * 2, h);

    volSlider.setBounds(0, h * 3, getWidth(), h);
    speedSlider.setBounds(0, h * 4, getWidth(), h);
    positionSlider.setBounds(0, h * 5, getWidth(), h);

}

void DeckGUI::buttonClicked(juce::Button *button) {
    if (button == &loopButton && player->isLoaded()) {
        player->setLooping(!player->isLooping());
        if (player->isLooping()) {
            loopButton.setColour(TextButton::buttonColourId, Colours::darkred);
        } else {
            loopButton.removeColour(TextButton::buttonColourId);
        }
    }

    if (button == &playPauseButton && player->isLoaded()) {
        if (player->isPlaying()) {
            player->stop();
            playPauseButton.setButtonText("Play");
            playPauseButton.removeColour(TextButton::buttonColourId);
        } else {
            player->start();
            playPauseButton.setButtonText("Pause");
            playPauseButton.setColour(TextButton::buttonColourId, Colours::darkred);
        }
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

