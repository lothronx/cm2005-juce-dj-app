#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "CustomLookAndFeel.h"
#include "WaveformDisplay.h"
#include "JogWheel.h"
#include "TransportControls.h"
#include "SpeedSlider.h"
#include "VolumeSlider.h"
#include "VUMeter.h"

class DeckGUI
        : public juce::Component,
          public juce::FileDragAndDropTarget{

public:
    DeckGUI(DJAudioPlayer *player,
            AudioFormatManager &formatManagerToUse,
            AudioThumbnailCache &cacheToUse,
            const Colour &_colour,
            const String &deckName);

    ~DeckGUI() override;

    void paint(juce::Graphics &g) override;

    void resized() override;

    bool isInterestedInFileDrag(const juce::StringArray &files) override;

    void filesDropped(const juce::StringArray &files, int x, int y) override;

private:
    DJAudioPlayer *player;

    bool isLeftDeck;

    CustomLookAndFeel customLookAndFeel;

    WaveformDisplay waveformDisplay;
    JogWheel jogWheel;
    TransportControls transportControls;
    SpeedSlider speedSlider;
    VolumeSlider volumeSlider;
    VUMeter vuMeter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};