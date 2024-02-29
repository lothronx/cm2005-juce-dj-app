#pragma once
#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource {

public:
    DJAudioPlayer();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources() override;

    void loadURL(const juce::URL &audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double relativePosition);
    void start();
    void stop();

private:
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
};