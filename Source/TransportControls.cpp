#include "TransportControls.h"


TransportControls::TransportControls(DJAudioPlayer *_player, WaveformDisplay *_waveformDisplay) : player{_player},
                                                                                                  waveformDisplay{
                                                                                                          _waveformDisplay} {

    loadButton.setToggleable(true);
    loadButton.setToggleState(true, dontSendNotification);
    playPauseButton.setToggleable(true);
    loopButton.setToggleable(true);

    addAndMakeVisible(loadButton);
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(loopButton);

    player->addChangeListener(this);
    loadButton.addListener(this);
    playPauseButton.addListener(this);
    loopButton.addListener(this);
}

void TransportControls::paint(juce::Graphics &g) {}

void TransportControls::resized() {
    auto h = getHeight() / 20;
    auto w = getWidth() / 33;

    loadButton.setBounds(w * 3, h * 5, w * 7, h * 10);
    playPauseButton.setBounds(loadButton.getX() + w * 10,
                              loadButton.getY(),
                              loadButton.getWidth(),
                              loadButton.getHeight());
    loopButton.setBounds(playPauseButton.getX() + w * 10,
                         playPauseButton.getY(),
                         playPauseButton.getWidth(),
                         playPauseButton.getHeight());
}

void TransportControls::buttonClicked(juce::Button *button) {
    if (button == &loadButton) {
        fChooser.launchAsync(FileBrowserComponent::canSelectFiles,
                             [this](const FileChooser &chooser) {
                                 player->loadURL(URL{chooser.getResult()});
                                 waveformDisplay->loadURL(URL{chooser.getResult()});
                             });
    }

    if (button == &playPauseButton && player->isLoaded()) {
        player->isPlaying() ? player->stop()
                            : player->start();
    }

    if (button == &loopButton && player->isLoaded()) {
        player->setLooping(!player->isLooping());
    }

}

void TransportControls::changeListenerCallback(juce::ChangeBroadcaster *source) {

    loadButton.setToggleState(!player->isLoaded(), dontSendNotification);

    playPauseButton.setToggleState(player->isPlaying(), dontSendNotification);
    playPauseButton.setButtonText(playPauseButton.getToggleState() ? "Pause" : "Play");

    loopButton.setToggleState(player->isLooping(), dontSendNotification);

}
