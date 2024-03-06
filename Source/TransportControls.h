
#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

class TransportControls : public juce::Component,
                          public juce::Button::Listener,
                          public juce::ChangeListener {
public:
    TransportControls(DJAudioPlayer *player, WaveformDisplay *waveformDisplay);

    void paint(juce::Graphics &) override;

    void resized() override;

    void buttonClicked(juce::Button *button) override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    DJAudioPlayer *player;
    WaveformDisplay *waveformDisplay;

    TextButton loadButton{"Load"};
    TextButton playPauseButton{"Play"};
    TextButton loopButton{"Loop"};

    juce::FileChooser fChooser{"Select a file..."};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportControls)
};
