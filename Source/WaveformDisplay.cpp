#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay() {

}

void WaveformDisplay::paint(Graphics &g) {
    g.setColour(Colours::orange);
    g.setFont(15.0f);
    g.drawText("File not loaded...", getLocalBounds(), Justification::centred, true);
}

void WaveformDisplay::resized() {
    Component::resized();
}


