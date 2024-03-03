#pragma once
#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource{

public:
    explicit DJAudioPlayer(AudioFormatManager& _formatManager);

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources() override;

    void loadURL(const juce::URL &audioURL);

    void setGain(double gain);
    void setSpeed(double ratio);
    void setPositionRelative(double relativePosition);
    double getPositionRelative() const;
    void setLooping(bool shouldLoop);

    bool isLoaded() const;
    bool isPlaying() const;
    bool isLooping() const;

    void start();
    void stop();



private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
};