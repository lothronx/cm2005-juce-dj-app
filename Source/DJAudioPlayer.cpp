#include "DJAudioPlayer.h"

//==============================================================================
DJAudioPlayer::DJAudioPlayer(AudioFormatManager &_formatManager)
        : formatManager{_formatManager} {}

//==============================================================================
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
/////////////////////// I wrote the following code //////////////////////
    // Initialize the DSP filters
    lowFilter.state =
            juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 200, 1.0, 1.0);
    midFilter.state =
            juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 1000, 1.0, 1.0);
    highFilter.state =
            juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 2000, 1.0, 1.0);

    juce::dsp::ProcessSpec spec{};
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<uint32>(samplesPerBlockExpected);
    spec.numChannels = 2;

    lowFilter.prepare(spec);
    midFilter.prepare(spec);
    highFilter.prepare(spec);
//////////////////////////// End of my code ////////////////////////////

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
/////////////////////// I wrote the following code //////////////////////
    filterSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    // Initialize the original and resample sample rates
    originalSampleRate = sampleRate;
    resampleRate = sampleRate;
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    // Clear the buffer if there is no reader source
    if (readerSource == nullptr) {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    // Reset the position to the beginning if the stream has finished
    if (transportSource.hasStreamFinished()) transportSource.setPosition(0);

    // Process the audio block through the DSP filters
    dsp::AudioBlock<float> block(*bufferToFill.buffer);
    dsp::ProcessContextReplacing<float> context(block);
    lowFilter.process(context);
    midFilter.process(context);
    highFilter.process(context);

    filterSource.getNextAudioBlock(bufferToFill);

    // Calculate the RMS level of the current audio block
    float rms = bufferToFill.buffer->getRMSLevel(0,
                                                 0,
                                                 bufferToFill.buffer->getNumSamples());
    rmsInDb = juce::Decibels::gainToDecibels(rms);
}
//////////////////////////// End of my code ////////////////////////////

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
/////////////////////// I wrote the following code //////////////////////
    filterSource.releaseResources();
}

//==============================================================================
void DJAudioPlayer::loadURL(const juce::URL &audioURL) {
    // Create an audio format reader from the audio file
    auto options =
            juce::URL::InputStreamOptions(juce::URL::ParameterHandling::inAddress);

    auto *reader =
            formatManager.createReaderFor(audioURL.createInputStream(options));

    // Set the transport source and reader source
    if (reader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newSource(
                new AudioFormatReaderSource(reader, true));

        transportSource.setSource(newSource.get(),
                                  0,
                                  nullptr,
                                  reader->sampleRate);

        readerSource = std::move(newSource);

        fileName = audioURL.getLocalFile().getFileName();

        sendChangeMessage();
    }
}

bool DJAudioPlayer::isLoaded() const {
    return static_cast<bool>(readerSource);
}

//==============================================================================
juce::String DJAudioPlayer::getFileName() const {
    return fileName;
}

//==============================================================================
juce::String DJAudioPlayer::getElapsedTime() const {
    auto posInSecs = transportSource.getCurrentPosition();

    int minutes = static_cast<int>(posInSecs) / 60;
    int wholeSeconds = static_cast<int>(posInSecs) % 60;
    double fractionalSeconds = posInSecs - static_cast<double>(static_cast<int>(posInSecs));
    int tenthsOfSecond = static_cast<int>(fractionalSeconds * 10.0);

    return juce::String::formatted("%02d:%02d.%1d", minutes, wholeSeconds, tenthsOfSecond);
}
//////////////////////////// End of my code ////////////////////////////

//==============================================================================
double DJAudioPlayer::getPositionRelative() const {
    if (isLoaded()) {
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    }
    return 0.0;
}

void DJAudioPlayer::setPositionRelative(double relativePosition) {
    double posInSecs = transportSource.getLengthInSeconds() * relativePosition;
    transportSource.setPosition(posInSecs);
}

//==============================================================================
/////////////////////// I wrote the following code //////////////////////
void DJAudioPlayer::setSpeed(double speedFactor) {
    // Because the speed factor is in percentage, the resampling ratio is calculated as follows:
    // For example, if the speed factor is +50%, the resampling ratio is 1.5.
    double ratio = 1 + (speedFactor / 100);
    resampleSource.setResamplingRatio(ratio);
    resampleRate = originalSampleRate * ratio;
}
//////////////////////////// End of my code ////////////////////////////

//==============================================================================
double DJAudioPlayer::getGain() const {
    return transportSource.getGain();
}

void DJAudioPlayer::setGain(double gain) {
    if (gain < 0 || gain > 1.0) {
        std::cout << "DJAudioPlayer::setGain: warning set gain " << gain << " out of range" << std::endl;
    } else {
        transportSource.setGain(static_cast<float>(gain));
    }
    sendChangeMessage();
}

//==============================================================================
/////////////////////// I wrote the following code //////////////////////
void DJAudioPlayer::setLowEQ(float gainInDb) {
    // Change the makeLowShelf() filter gain factor
    filterSource.setCoefficients(IIRCoefficients::makeLowShelf(
            resampleRate,
            200,
            1.0,
            juce::Decibels::decibelsToGain(gainInDb)));
}

void DJAudioPlayer::setMidEQ(float gainInDb) {
    // Change the makePeakFilter() filter gain factor
    filterSource.setCoefficients(IIRCoefficients::makePeakFilter(
            resampleRate,
            1000,
            1.0,
            juce::Decibels::decibelsToGain(gainInDb)));
}

void DJAudioPlayer::setHighEQ(float gainInDb) {
    // Change the makeHighShelf() filter gain factor
    filterSource.setCoefficients(IIRCoefficients::makeHighShelf(
            resampleRate,
            2000,
            1.0,
            juce::Decibels::decibelsToGain(gainInDb)));
}

//==============================================================================
float DJAudioPlayer::getRMSInDb() const {
    return rmsInDb;
}

//==============================================================================
void DJAudioPlayer::setLooping(bool shouldLoop) {
    readerSource->setLooping(shouldLoop);
    sendChangeMessage();
}

bool DJAudioPlayer::isLooping() const {
    return transportSource.isLooping();
}
//////////////////////////// End of my code ////////////////////////////

//==============================================================================
void DJAudioPlayer::start() {
    transportSource.start();
/////////////////////// I wrote the following code //////////////////////
    startTimer(100);
    sendChangeMessage();
//////////////////////////// End of my code ////////////////////////////
}

void DJAudioPlayer::stop() {
    transportSource.stop();
}

/////////////////////// I wrote the following code //////////////////////
bool DJAudioPlayer::isPlaying() const {
    return transportSource.isPlaying();
}

//==============================================================================
void DJAudioPlayer::timerCallback() {
    // If the audio playback has stopped playing for whatever reason
    // (not necessarily because the user pressed the stop button,
    // but could be because the audio file has finished),
    // stop the timer and send a change message to notify the listeners.
    if (!transportSource.isPlaying()) {
        stopTimer();
        sendChangeMessage();
    }
}
//////////////////////////// End of my code ////////////////////////////