#include "MainComponent.h"
#include <utility>

//==============================================================================
MainComponent::MainComponent() {
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio)) {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
                                          [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    } else {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(2, 2);
    }

//    playButton.addListener(this);
//    stopButton.addListener(this);
//    loadButton.addListener(this);
//    volSlider.addListener(this);
//    speedSlider.addListener(this);
//    positionSlider.addListener(this);
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);

}

MainComponent::~MainComponent() {
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    player1.getNextAudioBlock(bufferToFill);

//    auto *leftChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
//    auto *rightChan = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
//
//    for (auto i = 0; i < bufferToFill.numSamples; ++i) {
//        double sample = sin(phase) * 0.125;
//        leftChan[i] = sample;
//        rightChan[i] = sample;
//        phase += dPhase;
//    }
}

void MainComponent::releaseResources() {
    player1.releaseResources();
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    deckGUI1.setBounds(0, 0, getWidth() / 2, getHeight());
    deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}

void MainComponent::buttonClicked(juce::Button *button) {
//    if (button == &playButton) {
//        player1.start();
//    }
//    if (button == &stopButton) {
//        player1.stop();
//    }
//    if (button == &loadButton) {
//        fChooser.launchAsync(FileBrowserComponent::canSelectFiles, [this](const FileChooser &chooser) {
//            player1.loadURL(URL{chooser.getResult()});
//        });
//    }
}

void MainComponent::sliderValueChanged(juce::Slider *slider) {
//    if (slider == &volSlider) {
//        player1.setGain(slider->getValue());
//    }
//    if (slider == &speedSlider) {
//        player1.setSpeed(slider->getValue());
//    }
//    if (slider == &positionSlider) {
//        player1.setPosition(slider->getValue());
//    }
}

