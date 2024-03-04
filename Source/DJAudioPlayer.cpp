#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager &_formatManager)
        : formatManager{_formatManager} {}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    if (readerSource == nullptr) {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    resampleSource.getNextAudioBlock(bufferToFill);

    if (transportSource.hasStreamFinished()) {
        transportSource.setPosition(0);
    }
}

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(const juce::URL &audioURL) {
    auto options = juce::URL::InputStreamOptions(juce::URL::ParameterHandling::inAddress);

    auto *reader = formatManager.createReaderFor(
            audioURL.createInputStream(options));

    if (reader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource = std::move(newSource);
        sendChangeMessage();
    }
}

void DJAudioPlayer::setGain(double gain) {
    if (gain < 0 || gain > 1.0) {
        std::cout << "DJAudioPlayer::setGain: warning set gain " << gain << " out of range" << std::endl;
    } else {
        transportSource.setGain(static_cast<float>(gain));
    }
}

void DJAudioPlayer::setTempo(double relativeSpeedInPercent) {
    double tempo = 1 + (relativeSpeedInPercent / 100);
    resampleSource.setResamplingRatio(tempo);

}

void DJAudioPlayer::setPositionRelative(double relativePosition) {
    double posInSecs = transportSource.getLengthInSeconds() * relativePosition;
    transportSource.setPosition(posInSecs);
}

double DJAudioPlayer::getPositionRelative() const {
    if (static_cast<bool>(transportSource.getLengthInSeconds())) {
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    }
    return 0.0;
}

void DJAudioPlayer::setLooping(bool shouldLoop) {
    readerSource->setLooping(shouldLoop);
    sendChangeMessage();
}

void DJAudioPlayer::start() {
    transportSource.start();
    sendChangeMessage();
}

void DJAudioPlayer::stop() {
    transportSource.stop();
    sendChangeMessage();
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

