#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "CustomLookAndFeel.h"
#include "WaveformDisplay.h"
#include "JogWheel.h"
#include "TransportControls.h"

class DeckGUI
        : public juce::Component,
          public juce::Slider::Listener,
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

    void sliderValueChanged(juce::Slider *slider) override;

    bool isInterestedInFileDrag(const juce::StringArray &files) override;

    void filesDropped(const juce::StringArray &files, int x, int y) override;

private:
    DJAudioPlayer *player;

    bool isLeftDeck;

    CustomLookAndFeel customLookAndFeel;

    WaveformDisplay waveformDisplay;

    JogWheel jogWheel;

    TransportControls transportControls;

    Label speedLabel;
    Slider speedSlider;

    Label volLabel;
    Slider volSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};