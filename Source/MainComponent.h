#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "Crossfader.h"

class MainComponent
        : public juce::AudioAppComponent {

public:

    //==============================================================================
    /** Creates the main component.
     * The main component comprises two DeckGUIs and a Crossfader. */
    MainComponent();

    /** Destructor. */
    ~MainComponent() override;

    //==============================================================================
    /** Implementation of the AudioAppComponent method. */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /** Implementation of the AudioAppComponent method. */
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

    /** Implementation of the AudioAppComponent method. */
    void releaseResources() override;

    //==============================================================================
    /** Fills the background of the window with the color of the background.
     * Draws the Otodecks logo on the top center.
     * */
    void paint(juce::Graphics &g) override;

    /** Resizes the GUI components. */
    void resized() override;

private:
    //==============================================================================
    AudioFormatManager formatManager;

    AudioThumbnailCache thumbCache{100};

    MixerAudioSource mixerSource;

    /////////////////////// I wrote the following code //////////////////////
    // The color scheme
    juce::Colour color1 = juce::Colours::skyblue;
    juce::Colour color2 = juce::Colours::salmon;
    //////////////////////////// End of my code ////////////////////////////

    // The audio sources
    DJAudioPlayer player1{formatManager};
    DJAudioPlayer player2{formatManager};

    /////////////////////// I wrote the following code //////////////////////
    // The GUI subcomponents
    DeckGUI deckGUI1{&player1, formatManager, thumbCache, color1, "A"};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache, color2, "B"};
    Crossfader crossfader{&player1, &player2, color1, color2};
    //////////////////////////// End of my code ////////////////////////////

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

