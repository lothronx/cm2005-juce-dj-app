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

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    speedSlider.addListener(this);
    speedSlider.setRange(0.5, 2.0);
    speedSlider.setValue(1.0);
}

MainComponent::~MainComponent() {
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    //    phase = 0.0;
    //    dPhase = 0.001;

    formatManager.registerBasicFormats();

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {

    resampleSource.getNextAudioBlock(bufferToFill);

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
    transportSource.releaseResources();
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
    auto h = getHeight() / 5;
    loadButton.setBounds(getWidth() / 2 - 50, 0, 100, 100);
    playButton.setBounds(getWidth() / 2 - 50, h, 100, 100);
    stopButton.setBounds(getWidth() / 2 - 50, h * 2, 100, 100);

    volSlider.setBounds(getWidth() / 4, h * 3, getWidth() / 2, 100);
    speedSlider.setBounds(getWidth() / 4, h * 4, getWidth() / 2, 100);
}

void MainComponent::buttonClicked(juce::Button *button) {
    if (button == &playButton) {
        transportSource.start();
    }
    if (button == &stopButton) {
        transportSource.stop();
    }
    if (button == &loadButton) {
        fChooser.launchAsync(FileBrowserComponent::canSelectFiles, [this](const FileChooser &chooser) {
            loadURL(URL{chooser.getResult()});
        });
    }
}

void MainComponent::sliderValueChanged(juce::Slider *slider) {
    if (slider == &volSlider) {
        transportSource.setGain(static_cast<float>(volSlider.getValue()));
    }
    if (slider == &speedSlider) {
        resampleSource.setResamplingRatio(speedSlider.getValue());
    }
}

void MainComponent::loadURL(const URL &audioURL) {
    auto *reader = formatManager.createReaderFor(
            audioURL.createInputStream(juce::URL::InputStreamOptions(juce::URL::ParameterHandling::inAddress)));

    if (reader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource = std::move(newSource);
    }
}
