#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/** WaveformDisplay is a GUI component that displays the deck name, the file name,
 * the elapsed time, and the waveform of an audio file.
 * It also allows the user to change the current playback position in the source stream via a slider
 */
class WaveformDisplay : public juce::Component,
/////////////////////// I wrote the following code //////////////////////
                        public juce::Timer,
                        public juce::Slider::Listener,
//////////////////////////// End of my code ////////////////////////////
                        public juce::ChangeListener {

public:
    //==============================================================================
    /** Creates a WaveformDisplay to display the deck name, the file name, the elapsed time, and the waveform of an audio file.
     * A WaveformDisplay also allows the user to change the current playback position in the source stream via a slider.
     * @param formatManagerToUse the audio format manager that is used to open the file
     * @param cacheToUse an instance of an AudioThumbnailCache - this provides a background
                            thread and storage that is used to by the thumbnail, and the cache
                            object can be shared between multiple thumbnails
     * @param player the DJAudioPlayer audio source
     * @param _deckName the name of the deck
     * @param _colour the colour scheme
     */
    WaveformDisplay(AudioFormatManager &formatManagerToUse,
                    AudioThumbnailCache &cacheToUse,
/////////////////////// I wrote the following code //////////////////////
                    DJAudioPlayer *player,
                    const juce::String &_deckName,
                    const juce::Colour &_colour);
//////////////////////////// End of my code ////////////////////////////

    /** Destructor. */
    ~WaveformDisplay() override;

    //==============================================================================
    /** Paints the background of the component. */
    void paint(juce::Graphics &g) override;

    /** Positions and sizes all the subcomponents of the WaveformDisplay. */
    void resized() override;

    //==============================================================================
/////////////////////// I wrote the following code //////////////////////
    /** Updates the elapsed time label and slider position at a regular interval. */
    void timerCallback() override;

    /** Changes the current playback position when the slider value changes. */
    void sliderValueChanged(juce::Slider *slider) override;
//////////////////////////// End of my code ////////////////////////////

    /** Repaints the waveform when the state of the DJAudioPlayer changes. */
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    //==============================================================================
    /** Draws the waveform and displays the file name when the file is loaded. */
    void loadURL(const juce::URL &audioURL);

private:
    //==============================================================================
    bool fileLoaded{false};

/////////////////////// I wrote the following code //////////////////////
    // True if this is the left deck, false if it is the right deck
    bool isLeftDeck;

    // The DJAudioPlayer audio source
    DJAudioPlayer *player;

    // The colour scheme
    juce::Colour colour;

    // The GUI subcomponents
    Label deckNameLabel;
    Label fileNameLabel{"File Name", "Drag a song on this deck to load it"};
    Label elapsedTimeLabel{"Elapsed Time", "00:00.0"};
    Slider positionSlider;
//////////////////////////// End of my code ////////////////////////////
    AudioThumbnail audioThumb;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};