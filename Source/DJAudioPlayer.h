#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

class DJAudioPlayer : public juce::AudioSource,
                      public ChangeBroadcaster,
                      private Timer {

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

    /** Changes the gain to apply to the output.
        @param gain  a factor by which to multiply the outgoing samples,
                        so 1.0 = 0dB, 0.5 = -6dB, 2.0 = 6dB, etc.
    */
    void setGain(double gain);

    void setLowEQ(float gainInDb);

    void setMidEQ(float gainInDb);

    void setHighEQ(float gainInDb);

    float getRMSInDb() const;

    void setLooping(bool shouldLoop);

    /** Starts playing (if a source has been selected).

        If it starts playing, this will send a message to any ChangeListeners
        that are registered with this object.
    */
    void start();

    /** Stops playing.

        If it's actually playing, this will send a message to any ChangeListeners
        that are registered with this object.
    */
    void stop();

    bool isLoaded() const;

    /** Returns true if it's currently playing. */
    bool isPlaying() const;

    bool isLooping() const;


private:
    AudioFormatManager &formatManager;

    std::unique_ptr<AudioFormatReaderSource> readerSource;

    AudioTransportSource transportSource;

    ResamplingAudioSource resampleSource{&transportSource, false, 2};

    IIRFilterAudioSource filterSource{&resampleSource, false};

    double originalSampleRate{};

    double resampleRate{};

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowFilter;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> midFilter;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highFilter;

    String fileName;

    // Root Mean Square (RMS) Level
    float rmsInDb{0.0f};

    void timerCallback() override;
};