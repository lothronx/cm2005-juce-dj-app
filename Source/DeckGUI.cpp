#include "DeckGUI.h"

DeckGUI::DeckGUI() {
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);

    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    speedSlider.setRange(0.0, 10.0);
    speedSlider.setValue(1.0);
    positionSlider.setRange(0.0, 1.0);
    positionSlider.setValue(0.0);
}

DeckGUI::~DeckGUI() {

}

void DeckGUI::paint(Graphics &g) {
    Component::paint(g);
}

void DeckGUI::resized() {
    auto h = getHeight() / 6;
    loadButton.setBounds(getWidth() / 2 - 50, 0, 100, 100);
    playButton.setBounds(getWidth() / 2 - 50, h, 100, 100);
    stopButton.setBounds(getWidth() / 2 - 50, h * 2, 100, 100);
    volSlider.setBounds(getWidth() / 4, h * 3, getWidth() / 2, 100);
    speedSlider.setBounds(getWidth() / 4, h * 4, getWidth() / 2, 100);
    positionSlider.setBounds(getWidth() / 4, h * 5, getWidth() / 2, 100);
}
