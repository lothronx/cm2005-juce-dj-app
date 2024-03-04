#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(AudioFormatManager &formatManagerToUse,
                                 AudioThumbnailCache &cacheToUse,
                                 const juce::Colour &_colour)
        : audioThumb{1000, formatManagerToUse, cacheToUse}, fileLoaded{false}, colour{_colour} {
    audioThumb.addChangeListener(this);
}

void WaveformDisplay::paint(Graphics &g) {
    if (fileLoaded) {
        g.fillAll(Colours::darkgrey);
        g.setColour(colour);
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0.0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);
    } else {
        g.fillAll(colour);
        g.setColour(Colours::white);
        g.setFont(20.0f);
        g.drawText("Drag a song on this deck to load it",
                   getLocalBounds(),
                   Justification::centred,
                   true);
    }
}

void WaveformDisplay::resized() {
    Component::resized();
}

void WaveformDisplay::loadURL(const URL &audioURL) {
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source) {
    repaint();
}
