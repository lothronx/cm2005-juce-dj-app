#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse,
                 const Colour &_colour)
        : player{_player}, colour{_colour}, waveformDisplay{formatManagerToUse, cacheToUse, _colour} {

    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(loopButton);

    positionSlider.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    loadButton.addListener(this);
    playPauseButton.addListener(this);
    loopButton.addListener(this);

    positionSlider.setRange(0.0, 1.0);
    positionSlider.setValue(0.0);
    positionSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    positionSlider.setColour(Slider::ColourIds::trackColourId, Colours::black.withAlpha(0.3f));
    positionSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    speedSlider.setNormalisableRange(NormalisableRange<double>(0.5, 2.0, 0.01));
    speedSlider.setValue(1.0);
    speedSlider.setSkewFactorFromMidPoint(1.0);
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setColour(Slider::ColourIds::trackColourId, colour.withAlpha(0.6f));
    speedSlider.setColour(Slider::ColourIds::thumbColourId, colour);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);

    speedLabel.setText("Pitch", dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, false);

    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);

    startTimer(100);
}


DeckGUI::~DeckGUI() {
    stopTimer();
    speedSlider.setLookAndFeel(nullptr);
}

void DeckGUI::paint(Graphics &g) {
    Component::paint(g);
}

void DeckGUI::resized() {
    auto h = getHeight() / 10;
    auto w = getWidth() / 10;

    waveformDisplay.setBounds(0, 0, getWidth(), h * 2);
    positionSlider.setBounds(0, 0, getWidth(), h * 2);

    speedSlider.setBounds(w * 9, h * 3, w, h * 4);
    volSlider.setBounds(w * 8, h * 3, w, h * 4);

    loadButton.setBounds(w, h * 8, w * 2, h);
    playPauseButton.setBounds(w * 4, h * 8, w * 2, h);
    loopButton.setBounds(w * 7, h * 8, w * 2, h);
}

void DeckGUI::buttonClicked(juce::Button *button) {
    if (button == &loopButton && player->isLoaded()) {
        player->setLooping(!player->isLooping());
        if (player->isLooping()) {
            loopButton.setColour(TextButton::buttonColourId, colour);
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
            playPauseButton.setColour(TextButton::buttonColourId, colour);
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

    if (!player->isPlaying()) {
        playPauseButton.removeColour(TextButton::buttonColourId);
        playPauseButton.setButtonText("Play");
    }
}

