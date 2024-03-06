
#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class TransportControls : public juce::Component,
                          public juce::Button::Listener,
                          public juce::ChangeListener {
public:
    TransportControls(DJAudioPlayer *player);

    void paint(juce::Graphics &) override;

    void resized() override;

    void buttonClicked(juce::Button *button) override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    DJAudioPlayer *player;

    TextButton loadButton{"load"};
    TextButton playPauseButton{"play"};
    TextButton loopButton{"loop"};

    juce::FileChooser fChooser{"Select a file..."};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportControls)
};
