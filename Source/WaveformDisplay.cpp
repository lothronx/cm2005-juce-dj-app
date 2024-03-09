#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager &formatManagerToUse,
                                 AudioThumbnailCache &cacheToUse,
/////////////////////// I wrote the following code //////////////////////
                                 DJAudioPlayer *_player,
                                 const juce::String &_deckName,
                                 const juce::Colour &_colour)
        : player{_player}
        , colour{_colour}
        , deckNameLabel{"Deck Name", _deckName}
//////////////////////////// End of my code ////////////////////////////
        , audioThumb{1000, formatManagerToUse, cacheToUse} {

/////////////////////// I wrote the following code //////////////////////
    // Check if the current deck is the left deck or the right one
    // This will be used to position the subcomponents in a mirrored way
    isLeftDeck = deckNameLabel.getText() == "A";

    // Initialize the labels
    deckNameLabel.setFont(Font(30.0f, Font::bold));
    deckNameLabel.setJustificationType(Justification::centred);

    fileNameLabel.setFont(Font(20.0f, Font::bold));
    fileNameLabel.setJustificationType(
            isLeftDeck ? juce::Justification::centredLeft : juce::Justification::centredRight);

    elapsedTimeLabel.setJustificationType(
            isLeftDeck ? juce::Justification::centredRight : juce::Justification::centredLeft);

    // Initialize the position slider
    // The position slider is a linear bar that represents the current relative position in the audio file
    // It ranges from 0 to 1
    positionSlider.setRange(0.0, 1.0);
    positionSlider.setValue(0.0);
    positionSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    positionSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(deckNameLabel);
    addAndMakeVisible(fileNameLabel);
    addAndMakeVisible(elapsedTimeLabel);
    addAndMakeVisible(positionSlider);

    positionSlider.addListener(this);
//////////////////////////// End of my code ////////////////////////////
    audioThumb.addChangeListener(this);

/////////////////////// I wrote the following code //////////////////////
    startTimer(1000 / 60); // 60 FPS
}

WaveformDisplay::~WaveformDisplay() {
    stopTimer();
}

//==============================================================================
void WaveformDisplay::paint(Graphics &g) {
    // The component background
    g.fillAll(Colours::darkgrey);

    // The deck name label background
    g.setColour(colour);
    g.fillRect(deckNameLabel.getBounds());

    // The division line between the file name and the waveform
    g.setColour(Colours::grey.withAlpha(0.5f));
    g.drawLine(static_cast<float>(fileNameLabel.getX()), static_cast<float>(fileNameLabel.getBottom()),
               static_cast<float>(fileNameLabel.getRight()), static_cast<float>(fileNameLabel.getBottom()), 1);
//////////////////////////// End of my code ////////////////////////////

    // The waveform. It underlies the position slider
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

/////////////////////// I wrote the following code //////////////////////
void WaveformDisplay::resized() {
    auto h = getHeight();
    auto w = getWidth();

    // Positions the subcomponents.
    // The deck name label is on the far end
    // The file name and the elapsed time labels are displayed on the top half
    // The position slider is on the bottom half. It overlaps the waveform
    deckNameLabel.setBounds(isLeftDeck ? 0 : w * 37 / 40, 0, w * 3 / 40, h);
    fileNameLabel.setBounds(isLeftDeck ? w * 4 / 40 : w / 40, 0, w * 35 / 40, h / 2);
    elapsedTimeLabel.setBounds(fileNameLabel.getBounds());
    positionSlider.setBounds(isLeftDeck ? w * 3 / 40 : 0, h / 2, w * 37 / 40, h / 2);
}

//==============================================================================
void WaveformDisplay::timerCallback() {
    positionSlider.setValue(player->getPositionRelative(), dontSendNotification);
    elapsedTimeLabel.setText(player->getElapsedTime(), dontSendNotification);
}

void WaveformDisplay::sliderValueChanged(juce::Slider *slider) {
    player->setPositionRelative(slider->getValue());
}
//////////////////////////// End of my code ////////////////////////////

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source) {
    repaint();
}

//==============================================================================
void WaveformDisplay::loadURL(const URL &audioURL) {
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
/////////////////////// I wrote the following code //////////////////////
    // Update the file name label when the file is loaded
    if (fileLoaded) fileNameLabel.setText(player->getFileName(), dontSendNotification);
//////////////////////////// End of my code ////////////////////////////
}

