#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(AudioFormatManager &formatManagerToUse,
                                 AudioThumbnailCache &cacheToUse)
                                 : audioThumb{1000, formatManagerToUse, cacheToUse} {}

void WaveformDisplay::paint(Graphics &g) {
    g.setColour(Colours::orange);
    g.setFont(15.0f);
    g.drawText("File not loaded...", getLocalBounds(), Justification::centred, true);
}

void WaveformDisplay::resized() {
    Component::resized();
}

void WaveformDisplay::loadURL(URL audioURL) {
    audioThumb.clear();
    audioThumb.setSource(new URLInputSource(audioURL));
}

