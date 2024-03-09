/////////////////////// I wrote the following code //////////////////////

#include "TransportControls.h"

//==============================================================================
TransportControls::TransportControls(DJAudioPlayer *_player, WaveformDisplay *_waveformDisplay)
        : player{_player}
        , waveformDisplay{_waveformDisplay} {

    // Set up the control buttons
    // All three buttons are toggle buttons (have an on and off state)
    // The load button is initially toggled on
    // The play/pause and loop buttons are initially toggled off
    loadButton.setToggleable(true);
    playPauseButton.setToggleable(true);
    loopButton.setToggleable(true);
    loadButton.setToggleState(true, dontSendNotification);

    addAndMakeVisible(loadButton);
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(loopButton);

    // In addition to listening for button clicks, the TransportControls also listens for changes in the DJAudioPlayer
    // Thus also needs to register itself as a listener for the DJAudioPlayer
    player->addChangeListener(this);
    loadButton.addListener(this);
    playPauseButton.addListener(this);
    loopButton.addListener(this);
}

//==============================================================================

void TransportControls::paint(juce::Graphics &g) {}

void TransportControls::resized() {
    auto h = getHeight();
    auto w = getWidth();

    // The three buttons are laid out horizontally left to right with space between them
    loadButton.setBounds(w * 3 / 33, h / 4, w * 7 / 33, h / 2);
    playPauseButton.setBounds(loadButton.getX() + w * 10 / 33,
                              loadButton.getY(),
                              loadButton.getWidth(),
                              loadButton.getHeight());
    loopButton.setBounds(playPauseButton.getX() + w * 10 / 33,
                         playPauseButton.getY(),
                         playPauseButton.getWidth(),
                         playPauseButton.getHeight());
}

//==============================================================================

void TransportControls::buttonClicked(juce::Button *button) {
    // When the load button is clicked, open a file chooser to select a file to load into both the DJAudioPlayer and the WaveformDisplay
    if (button == &loadButton) {
        fChooser.launchAsync(FileBrowserComponent::canSelectFiles,
                             [this](const FileChooser &chooser) {
                                 player->loadURL(URL{chooser.getResult()});
                                 waveformDisplay->loadURL(URL{chooser.getResult()});
                             });
    }

    // When the play/pause button is clicked, start or stop the DJAudioPlayer
    if (button == &playPauseButton && player->isLoaded()) {
        player->isPlaying() ? player->stop()
                            : player->start();
    }

    // When the loop button is clicked, toggle the looping state of the DJAudioPlayer
    if (button == &loopButton && player->isLoaded()) {
        player->setLooping(!player->isLooping());
    }

}

//==============================================================================

void TransportControls::changeListenerCallback(juce::ChangeBroadcaster *source) {
    // When the state of the DJAudioPlayer changes, update the state of the buttons accordingly
    loadButton.setToggleState(!player->isLoaded(), dontSendNotification);
    playPauseButton.setToggleState(player->isPlaying(), dontSendNotification);
    loopButton.setToggleState(player->isLooping(), dontSendNotification);

    // Also update the text on the play/pause button to reflect its state
    playPauseButton.setButtonText(playPauseButton.getToggleState() ? "Pause" : "Play");
}

//////////////////////////// End of my code ////////////////////////////