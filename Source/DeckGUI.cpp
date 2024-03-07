#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse,
                 const Colour &_colour,
                 const String &_deckName)
        : player{_player}, isLeftDeck{_deckName == "A"}, customLookAndFeel{_colour},
          waveformDisplay{formatManagerToUse, cacheToUse, _player, _deckName, _colour}, jogWheel{_player, _colour},
          transportControls{_player, &waveformDisplay}, speedSlider{_player}, volumeSlider{_player},
          vuMeter{_player, _colour} {

    setLookAndFeel(&customLookAndFeel);

    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(jogWheel);
    addAndMakeVisible(transportControls);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(vuMeter);
}


DeckGUI::~DeckGUI() {
    setLookAndFeel(nullptr);
}

void DeckGUI::paint(Graphics &g) {
    auto h = static_cast<float>(getHeight());
    auto w = static_cast<float>(getWidth());

    g.setColour(Colours::grey.withAlpha(0.5f));
    g.drawRect(isLeftDeck ? 0.0f : w * 1 / 5, 0.0f, w * 4 / 5, h, 1.0f);
    g.drawLine(isLeftDeck ? w * 4 / 5 : 0, h / 5, isLeftDeck ? w : w / 5, h / 5, 1.0f);
}

void DeckGUI::resized() {
    auto h = getHeight();
    auto w = getWidth();

    waveformDisplay.setBounds(isLeftDeck ? 0 : w * 10 / 50, 0, w * 40 / 50, h * 4 / 20);

    jogWheel.setBounds(isLeftDeck ? 0 : w * 17 / 50, h * 5 / 20, w * 33 / 50, h * 11 / 20);

    transportControls.setBounds(isLeftDeck ? 0 : w * 17 / 50, h * 16 / 20, w * 33 / 50, h * 4 / 20);

    speedSlider.setBounds(isLeftDeck ? w * 33 / 50 : w * 13 / 50, h * 6 / 20, w * 4 / 50, h * 9 / 20);

    vuMeter.setBounds(isLeftDeck ? w * 42 / 50 : w * 2 / 50, h * 5 / 20, w * 6 / 50, h * 7 / 20);

    volumeSlider.setBounds(isLeftDeck ? w * 40 / 50 : 0, h * 13 / 20, w * 10 / 50, h * 4 / 20);
}

bool DeckGUI::isInterestedInFileDrag(const StringArray &files) {
    return true;
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y) {
    player->loadURL(URL{File{files[0]}});
    waveformDisplay.loadURL(URL{File{files[0]}});
}