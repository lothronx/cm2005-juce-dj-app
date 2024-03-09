#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() {
    // The default size of the window
    setSize(1200, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio)) {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
                                          [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    } else {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(2, 2);
    }

    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    /////////////////////// I wrote the following code //////////////////////
    addAndMakeVisible(crossfader);
    //////////////////////////// End of my code ////////////////////////////

    // Register the basic audio formats
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent() {
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    // Prepare the audio players for the two decks
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);

    // Prepare the mixer to mix the audio from the two decks
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources() {
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    /////////////////////// I wrote the following code //////////////////////
    // Draw the Otodecks logo on the top center
    juce::ColourGradient gradient(color1,
                                  static_cast<float>(getWidth()) * 2 / 5,
                                  0,
                                  color2,
                                  static_cast<float>(getWidth()) * 3 / 5,
                                  static_cast<float>(getHeight()) / 5,
                                  false);
    g.setGradientFill(gradient);
    g.setFont(juce::Font("Futura", 58.0f, juce::Font::italic));
    g.drawText("Otodecks",
               getWidth() * 2 / 5,
               0,
               getWidth() / 5,
               getHeight() / 5,
               juce::Justification::centred,
               true);
    //////////////////////////// End of my code ////////////////////////////
}

void MainComponent::resized() {
    deckGUI1.setBounds(0, 0, getWidth() / 2, getHeight());
    deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    /////////////////////// I wrote the following code //////////////////////
    crossfader.setBounds(getWidth() * 2 / 5, getHeight() * 4 / 5, getWidth() / 5, getHeight() / 5);
    //////////////////////////// End of my code ////////////////////////////
}