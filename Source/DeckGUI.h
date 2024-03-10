#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
/////////////////////// I wrote the following code //////////////////////
#include "CustomLookAndFeel.h"
#include "WaveformDisplay.h"
#include "JogWheel.h"
#include "TransportControls.h"
#include "SpeedSlider.h"
#include "Knobs.h"
#include "VUMeter.h"
//////////////////////////// End of my code ////////////////////////////

/** DeckGUI is a GUI component that represents a single deck in the DJ application.
 * It contains all the controls and visual elements for a single deck, including the following:
 * - A waveform display section
 *   (including deck name, file name, elapsed time, and audio waveform display, and playback position control)
 * - A jog wheel
 * - Transport controls (including load, play/pause, loop buttons)
 * - A speed slider
 * - Knobs for adjusting the volume and EQ
 * - A VU meter
 */
class DeckGUI
        : public juce::Component,
          public juce::FileDragAndDropTarget {

public:
    //==============================================================================
    /** Creates a Deck GUI component that contains
     * all the controls and visual elements for a single DJAudioPlayer audio source.
     * @param player The DJAudioPlayer audio source to control
     * @param formatManagerToUse The AudioFormatManager to use for decoding audio files
     * @param cacheToUse The AudioThumbnailCache to use for caching audio thumbnails
     * @param _colour The colour to use for the GUI
     * @param _deckName The name of the deck ("A" or "B")
     */
    DeckGUI(DJAudioPlayer *player,
            AudioFormatManager &formatManagerToUse,
            AudioThumbnailCache &cacheToUse,
            const Colour &_colour,
            const String &deckName);

    /** Destructor */
    ~DeckGUI() override;

    //==============================================================================
    /** Draws the bounds of the deck */
    void paint(juce::Graphics &g) override;

    /** Positions and sizes the subcomponents */
    void resized() override;

    //==============================================================================
    /** Returns true if this component is interested in file drag events. */
    bool isInterestedInFileDrag(const juce::StringArray &files) override;

    /** Loads the dropped file into the DJAudioPlayer and WaveformDisplay. */
    void filesDropped(const juce::StringArray &files, int x, int y) override;

private:
    //==============================================================================
    // THE DJAudioPlayer audio source to display and control
    DJAudioPlayer *player;

/////////////////////// I wrote the following code //////////////////////
    // True if this is the left deck, false if it's the right deck
    bool isLeftDeck;

    // The custom look and feel
    CustomLookAndFeel customLookAndFeel;

    // The subcomponents
    WaveformDisplay waveformDisplay;
    JogWheel jogWheel;
    TransportControls transportControls;
    SpeedSlider speedSlider;
    Knobs knobs;
    VUMeter vuMeter;
//////////////////////////// End of my code ////////////////////////////

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};