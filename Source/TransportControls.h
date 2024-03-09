/////////////////////// I wrote the following code //////////////////////

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

/** TransportControls is a GUI component that allows the user to
 * control a DJAudioPlayer audio source and update a WaveformDisplay audio thumbnail.
 * It contains 3 toggle buttons:
 * - Load: opens a file chooser to select a file to load into the DJAudioPlayer,
 *         updates the WaveformDisplay with the new file
 * - Play/Pause: starts or stops the DJAudioPlayer
 * - Loop: toggles the looping state of the DJAudioPlayer
 * The buttons provide visual feedback to indicate their on/off state.
 * Users can click the buttons to toggle them on or off.
 * The buttons also listen for changes in the DJAudioPlayer and updates their on/off state accordingly.
 */
class TransportControls : public juce::Component,
                          public juce::Button::Listener,
                          public juce::ChangeListener {

public:
    //==============================================================================
    /** Creates a transport controls component to control a DJAudioPlayer audio source and update a WaveformDisplay audio thumbnail.
     * @param player the DJAudioPlayer audio source to control
     * @param waveformDisplay the WaveformDisplay audio thumbnail to update
     */
    TransportControls(DJAudioPlayer *player, WaveformDisplay *waveformDisplay);

    //==============================================================================
    /** Implementation of the Component method. */
    void paint(juce::Graphics &) override;

    /** Positions the buttons within the component. */
    void resized() override;

    //==============================================================================
    /** Responds to button clicks.
     * - When the load button is clicked, opens a file chooser
     *   to select a file to load into the DJAudioPlayer and the WaveformDisplay
     * - When the play/pause button is clicked, starts or stops the DJAudioPlayer
     * - When the loop button is clicked, toggles the looping state of the DJAudioPlayer
     * */
    void buttonClicked(juce::Button *button) override;

    //==============================================================================
    /** Listens for changes in the DJAudioPlayer and updates the buttons accordingly. */
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    //==============================================================================
    // The DJAudioPlayer and WaveformDisplay to control
    DJAudioPlayer *player;
    WaveformDisplay *waveformDisplay;

    // The GUI subcomponents
    TextButton loadButton{"Load"};
    TextButton playPauseButton{"Play"};
    TextButton loopButton{"Loop"};

    // The file chooser to select files to load
    juce::FileChooser fChooser{"Select a file..."};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportControls)
};

//////////////////////////// End of my code ////////////////////////////