#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class WaveformDisplay : public juce::Component,
                        public juce::Slider::Listener,
                        public juce::Timer,
                        public juce::ChangeListener {
public:
    WaveformDisplay(AudioFormatManager &formatManagerToUse,
                    AudioThumbnailCache &cacheToUse,
                    DJAudioPlayer *player,
                    const juce::String &_deckName,
                    const juce::Colour &_colour);

    ~WaveformDisplay() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

    void sliderValueChanged(juce::Slider *slider) override;

    void timerCallback() override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    void loadURL(const juce::URL& audioURL);

private:
    DJAudioPlayer *player;

    bool fileLoaded;

    juce::Colour colour;

    Label deckNameLabel;

    Label fileNameLabel;
    Label elapsedTimeLabel;

    AudioThumbnail audioThumb;
    Slider positionSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};