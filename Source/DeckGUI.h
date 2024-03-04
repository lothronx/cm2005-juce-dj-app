#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "SpinningDisc.h"
#include "CustomLookAndFeel.h"

class DeckGUI
        : public juce::Component,
          public juce::Button::Listener,
          public juce::Slider::Listener,
          public juce::FileDragAndDropTarget,
          public juce::Timer,
          public juce::ChangeListener{
public:
    DeckGUI(DJAudioPlayer *player,
            AudioFormatManager &formatManagerToUse,
            AudioThumbnailCache &cacheToUse,
            const Colour &_colour,
            const juce::String &deckName);

    ~DeckGUI() override;

    void paint(juce::Graphics &g) override;

    void resized() override;

    void buttonClicked(juce::Button *button) override;

    void sliderValueChanged(juce::Slider *slider) override;

    bool isInterestedInFileDrag(const juce::StringArray &files) override;

    void filesDropped(const juce::StringArray &files, int x, int y) override;

    void timerCallback() override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    juce::FileChooser fChooser{"Select a file..."};

    DJAudioPlayer *player;

    Colour colour;
    CustomLookAndFeel customLookAndFeel;

    Label deckNameLabel;

    Label fileNameLabel;
    Label elapsedTimeLabel;

    WaveformDisplay waveformDisplay;
    Slider positionSlider;

    SpinningDisc spinningDisc;

    Label speedLabel;
    Slider speedSlider;

    TextButton loadButton;
    TextButton playPauseButton;
    TextButton loopButton;

    Label volLabel;
    Slider volSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};