#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource,
                      public ChangeBroadcaster, private Timer{

public:
    explicit DJAudioPlayer(AudioFormatManager &_formatManager);

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

    void releaseResources() override;

    void loadURL(const juce::URL &audioURL);

    juce::String getFileName() const;

    juce::String getElapsedTime() const;

    double getPositionRelative() const;

    void setPositionRelative(double relativePosition);

    void setSpeed(double relativeSpeedInPercent);

    double getGain() const;

    void setGain(double gain);

    float getRMS() const;

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

    String fileName;

    // Root Mean Square (RMS) Level
    float rmsInDb {0.0f};


    void timerCallback() override;
};