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

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    speedSlider.addListener(this);
    speedSlider.setRange(0.0, 10.0);
    speedSlider.setValue(1.0);
    positionSlider.addListener(this);
    positionSlider.setRange(0.0, 1.0);
    positionSlider.setValue(0.0);
}

MainComponent::~MainComponent() {
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    //    phase = 0.0;
    //    dPhase = 0.001;

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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized() {
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto h = getHeight() / 6;
    loadButton.setBounds(getWidth() / 2 - 50, 0, 100, 100);
    playButton.setBounds(getWidth() / 2 - 50, h, 100, 100);
    stopButton.setBounds(getWidth() / 2 - 50, h * 2, 100, 100);

    volSlider.setBounds(getWidth() / 4, h * 3, getWidth() / 2, 100);
    speedSlider.setBounds(getWidth() / 4, h * 4, getWidth() / 2, 100);
    positionSlider.setBounds(getWidth() / 4, h * 5, getWidth() / 2, 100);
}

void MainComponent::buttonClicked(juce::Button *button) {
    if (button == &playButton) {
        player1.start();
    }
    if (button == &stopButton) {
        player1.stop();
    }
    if (button == &loadButton) {
        fChooser.launchAsync(FileBrowserComponent::canSelectFiles, [this](const FileChooser &chooser) {
            player1.loadURL(URL{chooser.getResult()});
        });
    }
}

void MainComponent::sliderValueChanged(juce::Slider *slider) {
    if (slider == &volSlider) {
        player1.setGain(slider->getValue());
    }
    if (slider == &speedSlider) {
        player1.setSpeed(slider->getValue());
    }
    if (slider == &positionSlider) {
        player1.setPosition(slider->getValue());
    }
}

