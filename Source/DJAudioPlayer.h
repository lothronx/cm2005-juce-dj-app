#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource,
                      public ChangeBroadcaster {

public:
    explicit DJAudioPlayer(AudioFormatManager &_formatManager);

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

    void releaseResources() override;

    void loadURL(const juce::URL &audioURL);

    void setGain(double gain);

    void setTempo(double relativeSpeedInPercent);

    void setPositionRelative(double relativePosition);

    double getPositionRelative() const;

    void setLooping(bool shouldLoop);

    void start();

    void stop();

    bool isLoaded() const;

    bool isPlaying() const;

    bool isLooping() const;

private:
    AudioFormatManager &formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
};