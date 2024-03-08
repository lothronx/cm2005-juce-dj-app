
#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager &_formatManager)
        : formatManager{_formatManager} {}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<uint32>(samplesPerBlockExpected);
    spec.numChannels = 2;

    lowFilter.state = juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 200, 1.0, 1.0);
    midFilter.state = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 1000, 1.0, 1.0);
    highFilter.state = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 2000, 1.0, 1.0);

    lowFilter.prepare(spec);
    midFilter.prepare(spec);
    highFilter.prepare(spec);

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    filterSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    if (readerSource == nullptr) {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    if (transportSource.hasStreamFinished()) transportSource.setPosition(0);

    filterSource.getNextAudioBlock(bufferToFill);

    dsp::AudioBlock<float> block(*bufferToFill.buffer);
    dsp::ProcessContextReplacing<float> context(block);
    lowFilter.process(context);
    midFilter.process(context);
    highFilter.process(context);

    float rms = bufferToFill.buffer->getRMSLevel(0, 0, bufferToFill.buffer->getNumSamples());
    rmsInDb = juce::Decibels::gainToDecibels(rms);
}

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
    filterSource.releaseResources();
}

void DJAudioPlayer::loadURL(const juce::URL &audioURL) {
    auto options = juce::URL::InputStreamOptions(juce::URL::ParameterHandling::inAddress);

    auto *reader = formatManager.createReaderFor(
            audioURL.createInputStream(options));

    if (reader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource = std::move(newSource);
        fileName = audioURL.getLocalFile().getFileName();
        sendChangeMessage();
    }
}

juce::String DJAudioPlayer::getFileName() const {
    return fileName;
}

juce::String DJAudioPlayer::getElapsedTime() const {
    auto posInSecs = transportSource.getCurrentPosition();

    int minutes = static_cast<int>(posInSecs) / 60;
    int wholeSeconds = static_cast<int>(posInSecs) % 60;
    double fractionalSeconds = posInSecs - static_cast<double>(static_cast<int>(posInSecs));
    int tenthsOfSecond = static_cast<int>(fractionalSeconds * 10.0);

    return juce::String::formatted("%02d:%02d.%1d", minutes, wholeSeconds, tenthsOfSecond);
}

double DJAudioPlayer::getPositionRelative() const {
    if (static_cast<bool>(transportSource.getLengthInSeconds())) {
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    }
    return 0.0;
}

void DJAudioPlayer::setPositionRelative(double relativePosition) {
    double posInSecs = transportSource.getLengthInSeconds() * relativePosition;
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setSpeed(double relativeSpeedInPercent) {
    double tempo = 1 + (relativeSpeedInPercent / 100);
    resampleSource.setResamplingRatio(tempo);
}

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

void DJAudioPlayer::setLowEQ(float gainInDb) {
    filterSource.setCoefficients(IIRCoefficients::makeLowShelf(spec.sampleRate, 200, 1.0, juce::Decibels::decibelsToGain(gainInDb)));
}

void DJAudioPlayer::setMidEQ(float gainInDb) {
    filterSource.setCoefficients(IIRCoefficients::makePeakFilter(spec.sampleRate, 1000, 1.0, juce::Decibels::decibelsToGain(gainInDb)));
}

void DJAudioPlayer::setHighEQ(float gainInDb) {
    filterSource.setCoefficients(IIRCoefficients::makeHighShelf(spec.sampleRate, 2000, 1.0, juce::Decibels::decibelsToGain(gainInDb)));
}

float DJAudioPlayer::getRMS() const {
    return rmsInDb;
}

void DJAudioPlayer::setLooping(bool shouldLoop) {
    readerSource->setLooping(shouldLoop);
    sendChangeMessage();
}

void DJAudioPlayer::start() {
    transportSource.start();
    startTimer(100);
    sendChangeMessage();
}

void DJAudioPlayer::stop() {
    transportSource.stop();
}

bool DJAudioPlayer::isLoaded() const {
    return static_cast<bool>(readerSource);
}

bool DJAudioPlayer::isPlaying() const {
    return transportSource.isPlaying();
}

bool DJAudioPlayer::isLooping() const {
    return transportSource.isLooping();
}

void DJAudioPlayer::timerCallback() {
    if (!transportSource.isPlaying()) {
        stopTimer();
        sendChangeMessage();
    }
}