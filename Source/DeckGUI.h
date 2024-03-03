#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

class DeckGUI
        : public juce::Component,
          public juce::Button::Listener,
          public juce::Slider::Listener,
          public juce::FileDragAndDropTarget,
          public juce::Timer {
public:
    DeckGUI(DJAudioPlayer *player,
                     AudioFormatManager &formatManagerToUse,
                     AudioThumbnailCache &cacheToUse);
    ~DeckGUI() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

    void buttonClicked(juce::Button *button) override;

    void sliderValueChanged(juce::Slider *slider) override;

    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    void timerCallback() override;

private:
    TextButton loadButton{"Load"};
    TextButton playPauseButton{"Play"};
    TextButton loopButton{"Loop"};

    Slider volSlider;
    Slider speedSlider;
    Slider positionSlider;

    juce::FileChooser fChooser{"Select a file..."};

    DJAudioPlayer *player;

    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};