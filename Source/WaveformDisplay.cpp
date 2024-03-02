#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(AudioFormatManager &formatManagerToUse,
                                 AudioThumbnailCache &cacheToUse)
                                 : audioThumb{1000,
                                              formatManagerToUse,
                                              cacheToUse}
                                 , fileLoaded{false} {
    audioThumb.addChangeListener(this);
}

void WaveformDisplay::paint(Graphics &g) {
    g.setColour(Colours::orange);
    g.setFont(15.0f);

    if (fileLoaded) {
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0.0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);
    } else{
        g.drawText("File not loaded...",
                   getLocalBounds(),
                   Justification::centred,
                   true);
    }
}

void WaveformDisplay::resized() {
    Component::resized();
}

void WaveformDisplay::loadURL(const URL& audioURL) {
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source) {
    repaint();
}

