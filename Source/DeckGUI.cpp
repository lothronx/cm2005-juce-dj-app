#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse,
                 const Colour &_colour)
        : player{_player}, colour{_colour}, customLookAndFeel{_colour},
          waveformDisplay{formatManagerToUse, cacheToUse, _colour} {
    setLookAndFeel(&customLookAndFeel);

    positionSlider.setRange(0.0, 1.0);
    positionSlider.setValue(0.0);
    positionSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    positionSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    speedLabel.setText("Tempo", dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, false);

    speedSlider.setNormalisableRange(NormalisableRange<double>(-50, 50, 1));
    speedSlider.setValue(0.0);
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    speedSlider.setTextValueSuffix(" %");

    volLabel.setText("Volume", dontSendNotification);
    volLabel.attachToComponent(&volSlider, false);

    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setDoubleClickReturnValue(true, 0.5);
    volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    loadButton.setButtonText("Load");
    loadButton.setToggleable(true);
    loadButton.setToggleState(true, dontSendNotification);

    playPauseButton.setButtonText("Play");
    playPauseButton.setToggleable(true);

    loopButton.setButtonText("Loop");
    loopButton.setToggleable(true);

    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(volLabel);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(loopButton);

    player->addChangeListener(this);
    positionSlider.addListener(this);
    speedSlider.addListener(this);
    volSlider.addListener(this);
    loadButton.addListener(this);
    playPauseButton.addListener(this);
    loopButton.addListener(this);

    startTimer(100);
}


DeckGUI::~DeckGUI() {
    stopTimer();
    setLookAndFeel(nullptr);
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

    volSlider.setBounds(w * 7, h * 3, w * 2, h * 4);

    loadButton.setBounds(w, h * 8, w * 2, h);
    playPauseButton.setBounds(w * 4, h * 8, w * 2, h);
    loopButton.setBounds(w * 7, h * 8, w * 2, h);
}

void DeckGUI::buttonClicked(juce::Button *button) {
    if (button == &loadButton) {
        fChooser.launchAsync(FileBrowserComponent::canSelectFiles,
                             [this](const FileChooser &chooser) {
                                 player->loadURL(URL{chooser.getResult()});
                                 waveformDisplay.loadURL(URL{chooser.getResult()});
                             });
    }

    if (button == &playPauseButton && player->isLoaded()) {
        player->isPlaying() ? player->stop()
                            : player->start();
    }

    if (button == &loopButton && player->isLoaded()) {
        player->setLooping(!player->isLooping());
    }
}

void DeckGUI::sliderValueChanged(juce::Slider *slider) {
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider) {
        player->setTempo(slider->getValue());
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
    waveformDisplay.loadURL(URL{File{files[0]}});
}

void DeckGUI::timerCallback() {
    positionSlider.setValue(player->getPositionRelative(), dontSendNotification);
}

void DeckGUI::changeListenerCallback(juce::ChangeBroadcaster *source) {
    if (source == player) {
        loadButton.setToggleState(!player->isLoaded(), dontSendNotification);

        playPauseButton.setToggleState(player->isPlaying(), dontSendNotification);
        playPauseButton.setButtonText(playPauseButton.getToggleState() ? "Pause" : "Play");

        loopButton.setToggleState(player->isLooping(), dontSendNotification);
    }
}