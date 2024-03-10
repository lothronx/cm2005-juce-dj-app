#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse,
/////////////////////// I wrote the following code //////////////////////
                 const Colour &_colour,
                 const String &_deckName)
        : player{_player}
        , isLeftDeck{_deckName == "A"}
        , customLookAndFeel{_colour}
        , waveformDisplay{formatManagerToUse, cacheToUse, _player, _deckName, _colour}
        , jogWheel{_player, _colour}
        , transportControls{_player, &waveformDisplay}
        , speedSlider{_player}
        , knobs{_player}
        , vuMeter{_player, _colour} {

    // Set the custom look and feel
    setLookAndFeel(&customLookAndFeel);

    // Add the subcomponents
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(jogWheel);
    addAndMakeVisible(transportControls);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(knobs);
    addAndMakeVisible(vuMeter);
}


DeckGUI::~DeckGUI() {
    // Reset the look and feel
    setLookAndFeel(nullptr);
}

//==============================================================================
void DeckGUI::paint(Graphics &g) {
    auto h = static_cast<float>(getHeight());
    auto w = static_cast<float>(getWidth());

    // Draw the deck outline
    g.setColour(Colours::grey.withAlpha(0.5f));
    g.drawRect(isLeftDeck ? 0.0f : w * 1 / 5, 0.0f, w * 4 / 5, h, 1.0f);
    g.drawLine(isLeftDeck ? w * 4 / 5 : 0, h / 5, isLeftDeck ? w : w / 5, h / 5, 1.0f);
}

void DeckGUI::resized() {
    auto h = getHeight();
    auto w = getWidth();

    // Position and size the subcomponents as such:
    // - The waveform display on top
    // - The jog wheel below the waveform display
    // - The transport controls below the jog wheel
    // - The speed slider to the right of the jog wheel
    // - The Knobs and the VU meter to the right of the deck
    waveformDisplay.setBounds(isLeftDeck ? 0 : w * 10 / 50, 0, w * 40 / 50, h * 4 / 20);
    jogWheel.setBounds(isLeftDeck ? 0 : w * 17 / 50, h * 5 / 20, w * 33 / 50, h * 11 / 20);
    transportControls.setBounds(isLeftDeck ? 0 : w * 17 / 50, h * 16 / 20, w * 33 / 50, h * 4 / 20);
    speedSlider.setBounds(isLeftDeck ? w * 33 / 50 : w * 13 / 50, h * 6 / 20, w * 4 / 50, h * 9 / 20);
    vuMeter.setBounds(isLeftDeck ? w * 49 / 50 - 5 : 5, h * 5 / 20, w / 50, h * 11 / 20);
    knobs.setBounds(isLeftDeck ? w * 40 / 50 : 0, h * 4 / 20, w * 10 / 50, h * 12 / 20);
}
//////////////////////////// End of my code ////////////////////////////

//==============================================================================
bool DeckGUI::isInterestedInFileDrag(const StringArray &files) {
    return true;
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y) {
    player->loadURL(URL{File{files[0]}});
    waveformDisplay.loadURL(URL{File{files[0]}});
}