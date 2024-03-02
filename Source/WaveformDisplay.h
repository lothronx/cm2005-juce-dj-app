#pragma once

#include <JuceHeader.h>

class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener {
public:
    WaveformDisplay(AudioFormatManager &formatManagerToUse,
                    AudioThumbnailCache &cacheToUse);

    void paint(juce::Graphics &g) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    void loadURL(const juce::URL& audioURL);

    void setPositionRelative(double relativePosition);

private:
    AudioThumbnail audioThumb;

    bool fileLoaded;

    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};