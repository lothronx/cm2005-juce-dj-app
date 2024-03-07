#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse,
                 const Colour &_colour,
                 const String &_deckName)
        : player{_player}, isLeftDeck{_deckName == "A"}, customLookAndFeel{_colour},
          waveformDisplay{formatManagerToUse, cacheToUse, _player, _deckName, _colour}, jogWheel{_player, _colour},
          transportControls{_player, &waveformDisplay}, speedSlider{_player}, knobs{_player},
          vuMeter{_player, _colour} {

    setLookAndFeel(&customLookAndFeel);

    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(jogWheel);
    addAndMakeVisible(transportControls);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(knobs);
    addAndMakeVisible(vuMeter);
}


DeckGUI::~DeckGUI() {
    setLookAndFeel(nullptr);
}

void DeckGUI::paint(Graphics &g) {
    Component::paint(g);

    g.setColour(Colours::grey.withAlpha(0.5f));
    g.drawRect(isLeftDeck ? 0 : getWidth() * 1 / 5, 0, getWidth() * 4 / 5, getHeight(), 1);
}

void DeckGUI::resized() {
    auto h = getHeight() / 100;
    auto w = getWidth() / 50;

    waveformDisplay.setBounds(isLeftDeck ? 0 : w * 10, 0, w * 40, h * 20);

    jogWheel.setBounds(isLeftDeck ? w * 0 : w * 17, h * 25, w * 33, h * 55);

    transportControls.setBounds(isLeftDeck ? 0 : w * 17, h * 80, w * 33, h * 20);

    speedSlider.setBounds(isLeftDeck ? w * 33 : w * 13, h * 30, w * 4, h * 45);

    knobs.setBounds(isLeftDeck ? w * 40 : 0, h * 15, w * 10, h * 70);

    vuMeter.setBounds(isLeftDeck ? getWidth() - w - 5 : 5, h * 20, w, h * 60);
}

bool DeckGUI::isInterestedInFileDrag(const StringArray &files) {
    return true;
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y) {
    player->loadURL(URL{File{files[0]}});
    waveformDisplay.loadURL(URL{File{files[0]}});
}