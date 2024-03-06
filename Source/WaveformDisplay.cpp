#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(AudioFormatManager &formatManagerToUse,
                                 AudioThumbnailCache &cacheToUse,
                                 DJAudioPlayer *_player,
                                 const juce::String &_deckName,
                                 const juce::Colour &_colour)
        : player{_player}, colour{_colour}, deckNameLabel{_deckName, _deckName},
          audioThumb{1000, formatManagerToUse, cacheToUse} {

    isLeftDeck = deckNameLabel.getText() == "A";

    deckNameLabel.setFont(Font(30.0f, Font::bold));
    deckNameLabel.setJustificationType(Justification::centred);

    fileNameLabel.setFont(Font(20.0f, Font::bold));
    fileNameLabel.setJustificationType(
            isLeftDeck ? juce::Justification::centredLeft : juce::Justification::centredRight);

    elapsedTimeLabel.setJustificationType(
            isLeftDeck ? juce::Justification::centredRight : juce::Justification::centredLeft);

    positionSlider.setRange(0.0, 1.0);
    positionSlider.setValue(0.0);
    positionSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    positionSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(deckNameLabel);
    addAndMakeVisible(fileNameLabel);
    addAndMakeVisible(elapsedTimeLabel);
    addAndMakeVisible(positionSlider);

    player->addChangeListener(this);
    audioThumb.addChangeListener(this);
    positionSlider.addListener(this);

    startTimer(1000 / 60);
}


WaveformDisplay::~WaveformDisplay() {
    stopTimer();
}


void WaveformDisplay::paint(Graphics &g) {

    g.fillAll(Colours::darkgrey);

    g.setColour(colour);
    g.fillRect(deckNameLabel.getBounds());

    g.setColour(Colours::grey.withAlpha(0.5f));
    g.drawLine(static_cast<float>(fileNameLabel.getX()), static_cast<float>(fileNameLabel.getBottom()),
               static_cast<float>(fileNameLabel.getRight()), static_cast<float>(fileNameLabel.getBottom()), 1);

    if (fileLoaded) {
        g.setColour(colour);
        audioThumb.drawChannel(g,
                               positionSlider.getBounds(),
                               0.0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);
    }
}

void WaveformDisplay::resized() {
    auto h = getHeight() / 2;
    auto w = getWidth() / 40;

    deckNameLabel.setBounds(isLeftDeck ? 0 : w * 37, 0, w * 3, h * 2);
    fileNameLabel.setBounds(isLeftDeck ? w * 3 : 0, 0, w * 37, h);
    elapsedTimeLabel.setBounds(fileNameLabel.getBounds());
    positionSlider.setBounds(isLeftDeck ? w * 3 : 0, h, w * 37, h);
}

void WaveformDisplay::sliderValueChanged(juce::Slider *slider) {

    player->setPositionRelative(slider->getValue());
}

void WaveformDisplay::timerCallback() {
    positionSlider.setValue(player->getPositionRelative(), dontSendNotification);
    elapsedTimeLabel.setText(player->getElapsedTime(), dontSendNotification);
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source) {
    repaint();
}

void WaveformDisplay::loadURL(const URL &audioURL) {
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    if (fileLoaded) fileNameLabel.setText(player->getFileName(), dontSendNotification);
}