#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse,
                 const Colour &_colour,
                 const String &_deckName)
        : player{_player}, isLeftDeck{_deckName == "A"}, customLookAndFeel{_colour},
          waveformDisplay{formatManagerToUse, cacheToUse, _player, _deckName, _colour}, jogWheel{_player, _colour},
          transportControls{_player, &waveformDisplay} {

    setLookAndFeel(&customLookAndFeel);

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


    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(jogWheel);
    addAndMakeVisible(transportControls);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(volLabel);
    addAndMakeVisible(volSlider);

    speedSlider.addListener(this);
    volSlider.addListener(this);
}


DeckGUI::~DeckGUI() {
    setLookAndFeel(nullptr);
}

void DeckGUI::paint(Graphics &g) {
    Component::paint(g);

    g.setColour(Colours::grey.withAlpha(0.5f));
    g.drawRect(isLeftDeck ? 0 : getWidth() * 1 / 5, 0, getWidth() * 4 / 5, getHeight(), 1);

    g.drawRoundedRectangle(static_cast<float>(speedSlider.getX() - 3),
                           static_cast<float>(speedSlider.getY() - 30),
                           static_cast<float>(speedSlider.getWidth() + 6),
                           static_cast<float>(speedSlider.getHeight() + 40),
                           10,
                           1);
}

void DeckGUI::resized() {
    auto h = getHeight() / 100;
    auto w = getWidth() / 50;

    waveformDisplay.setBounds(isLeftDeck ? 0 : w * 10, 0, w * 40, h * 20);

    jogWheel.setBounds(isLeftDeck ? w * 0 : w * 17, h * 25, w * 33, h * 55);

    transportControls.setBounds(isLeftDeck ? 0 : w * 17, h * 80, w * 33, h * 20);

    speedSlider.setBounds(isLeftDeck ? w * 33 : w * 13, h * 30, w * 4, h * 50);

    volSlider.setBounds(isLeftDeck ? w * 40 : 0, h * 15, w * 10, h * 10);
}

void DeckGUI::sliderValueChanged(juce::Slider *slider) {
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider) {
        player->setTempo(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const StringArray &files) {
    return true;
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y) {
    player->loadURL(URL{File{files[0]}});
    waveformDisplay.loadURL(URL{File{files[0]}});
}