#pragma once

#include <JuceHeader.h>
/////////////////////// I wrote the following code //////////////////////
#include <juce_dsp/juce_dsp.h>
//////////////////////////// End of my code ////////////////////////////

/** DJAudioPlayer is a class that handles audio playback.

    It is an AudioSource that can play audio files and manipulate their playback,
    such as position, speed, gain, and EQ.

    It is also a ChangeBroadcaster, so it can notify other objects when it loads a new file,
    starts or stops playing, changes the loop state, or changes the gain.
*/
class DJAudioPlayer : public juce::AudioSource,
/////////////////////// I wrote the following code //////////////////////
                      public ChangeBroadcaster,
                      private Timer {
//////////////////////////// End of my code ////////////////////////////

public:
    //==============================================================================
    /** Creates a DJAudioPlayer that handles audio playback.
        @param _formatManager  the AudioFormatManager to use for audio files.
     * */
    explicit DJAudioPlayer(AudioFormatManager &_formatManager);

    //==============================================================================
    /** Initializes the DSP filters and prepares the transport source for playing.
        @param samplesPerBlockExpected  the number of samples that the source
                                        will be expected to supply each time its
                                        getNextAudioBlock() method is called.
        @param sampleRate  the sample rate that the audio source is expected to use.
    */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /** Processes the next block of audio data and applies the DSP filters.
        @param bufferToFill  the buffer to fill with audio data.
    */
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

    /** Releases any resources that were allocated during playback.
    */
    void releaseResources() override;

    //==============================================================================
    /** Loads an audio file from a URL onto the audio player.
     * This will also send a message to any ChangeListeners that are registered with this object.
        @param audioURL  the URL of the audio file to load.
    */
    void loadURL(const juce::URL &audioURL);

/////////////////////// I wrote the following code //////////////////////
    /** Returns true if an audio file is currently loaded.
     * @return true if an audio file is currently loaded, false otherwise.
     */
    bool isLoaded() const;

    //==============================================================================
    /** Returns the name of the currently loaded audio file.
     * @return the name of the currently loaded audio file.
     */
    juce::String getFileName() const;

    //==============================================================================
    /** Returns the position that the next data block will be read from in the format "mm:ss.ms".
     * @return the elapsed time of the currently loaded audio file in the format "mm:ss.ms".
     */
    juce::String getElapsedTime() const;
//////////////////////////// End of my code ////////////////////////////

    //==============================================================================
    /** Returns the position that the next data block will be read from.
        This is a relative position, where 0.0 is the start and 1.0 is the end.
        @return the relative position of the audio file,
                where 0.0 is the start and 1.0 is the end.
    */
    double getPositionRelative() const;

    /** Changes the current playback position in the source stream.
        @param relativePosition  the relative position of the audio file,
                                 where 0.0 is the start and 1.0 is the end.
    */
    void setPositionRelative(double relativePosition);

    //==============================================================================
    /** Changes the speed of the audio playback.
        @param speedFactor  the factor of the speed change,
                            where 0.0 means no change,
                            1.0 means 1% faster, -1.0 means 1% slower, etc.
    */
    void setSpeed(double speedFactor);

    //==============================================================================
    /** Returns the current volume of the audio playback.
        @return the current volume of the audio playback,
                where 0.0 means silence, 1.0 means maximum volume.
    */
    double getGain() const;

    /** Changes the volume of the audio playback.
        This will also send a message to any ChangeListeners that are registered with this object.
        @param gain  the volume to be applied to the audio playback,
                     where 0.0 means silence, 1.0 means maximum volume.
    */
    void setGain(double gain);

    //==============================================================================
/////////////////////// I wrote the following code //////////////////////
    /** Changes the gain of the low frequency band of the audio playback.
        The low frequency band is defined as lower than 200 Hz.
        @param gainInDb  the gain factor to be applied to the low frequency band.
                         This gain factor is in decibels,
                         where 24 means +24 dB, -24 means -24 dB, etc.
    */
    void setLowEQ(float gainInDb);

    /** Changes the gain of the mid frequency band of the audio playback.
        The mid frequency band is a bandpass network with a center frequency of 1000 Hz.
        @param gainInDb  the gain factor to be applied to the mid frequency band.
                         This gain factor is in decibels,
                         where 24 means +24 dB, -24 means -24 dB, etc.
    */
    void setMidEQ(float gainInDb);

    /** Changes the gain of the high frequency band of the audio playback.
        The high frequency band is defined as higher than 2000 Hz.
        @param gainInDb  the gain factor to be applied to the high frequency band.
                         This gain factor is in decibels,
                         where 24 means +24 dB, -24 means -24 dB, etc.
    */
    void setHighEQ(float gainInDb);

    //==============================================================================
    /** Returns the Root Mean Square (RMS) Level of the current audio block.
        @return the RMS Level of the current audio block in decibels,
                   where -100.0 means silence, 0.0 means maximum volume.
    */
    float getRMSInDb() const;

    //==============================================================================
    /** Changes the loop state of the audio playback.
        This will also send a message to any ChangeListeners that are registered with this object.
        @param shouldLoop  true if the audio playback should loop, false otherwise.
    */
    void setLooping(bool shouldLoop);

    /** Returns true if the audio playback is currently looping.
        @return true if the audio playback is currently looping, false otherwise.
    */
    bool isLooping() const;
//////////////////////////// End of my code ////////////////////////////

    //==============================================================================
    /** Starts playing.
        This will send a message to any ChangeListeners that are registered with this object.
    */
    void start();

    /** Stops playing. */
    void stop();

/////////////////////// I wrote the following code //////////////////////
    /** Returns true if the audio playback is currently playing.
     * @return true if the audio playback is currently playing, false otherwise.
     */
    bool isPlaying() const;
//////////////////////////// End of my code ////////////////////////////

private:
    //==============================================================================
    AudioFormatManager &formatManager;

    //==============================================================================
    std::unique_ptr<AudioFormatReaderSource> readerSource;

    AudioTransportSource transportSource;

    ResamplingAudioSource resampleSource{&transportSource, false, 2};

/////////////////////// I wrote the following code //////////////////////
    // filterSource wraps resampleSource the same way resampleSource wraps transportSource
    IIRFilterAudioSource filterSource{&resampleSource, false};

    //==============================================================================
    String fileName;

    // Root Mean Square Level (average power) of the current audio block in decibels
    float rmsInDb{-100.0f};

    double originalSampleRate{};

    double resampleRate{};

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowFilter;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> midFilter;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highFilter;

    //==============================================================================
    /** Keeps checks whether the audio playback has stopped.
        This is used to stop the timer and send a message to any ChangeListeners that are registered with this object.
    */
    void timerCallback() override;
//////////////////////////// End of my code ////////////////////////////
};