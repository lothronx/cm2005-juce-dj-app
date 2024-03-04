#include "SpinningDisc.h"

SpinningDisc::SpinningDisc(const Colour &_colour)
        : colour{_colour} {
    startTimer(1000 / 60);
}

SpinningDisc::~SpinningDisc() {
    stopTimer();
}

void SpinningDisc::paint(juce::Graphics &g) {
    auto centreX = static_cast<float>(getWidth()) / 2;
    auto centreY = static_cast<float>(getHeight()) / 2;

    g.addTransform(juce::AffineTransform::rotation(rotationAngle, centreX, centreY));

    drawDisc(g, centreX, centreY);

}

void SpinningDisc::resized() {
}

void SpinningDisc::timerCallback() {
    if (isPlaying) {
        rotationAngle += rotationSpeed;
        rotationAngle = fmod(rotationAngle, juce::MathConstants<float>::twoPi);
        repaint();
    }
}

void SpinningDisc::setPlaying(bool shouldBePlaying) {
    isPlaying = shouldBePlaying;
}


void SpinningDisc::drawDisc(juce::Graphics &g, const float centreX, const float centreY) {
    auto radius = static_cast<float>(jmin(getWidth(), getHeight())) / 2 - 5;

    g.setColour(Colours::darkgrey);
    g.drawEllipse(centreX - radius, centreY - radius, radius * 2, radius * 2, 10);

    radius *= 0.75f;
    g.setColour(colour);
    juce::PathStrokeType strokeType(10.0f,
                                    juce::PathStrokeType::curved,
                                    juce::PathStrokeType::rounded);

    juce::Path arcPath1;
    arcPath1.addArc(centreX - radius,
                    centreY - radius,
                    radius * 2,
                    radius * 2,
                    juce::MathConstants<float>::pi * 0.25f,
                    juce::MathConstants<float>::pi * 0.75f,
                    true);
    g.strokePath(arcPath1, strokeType);

    juce::Path arcPath2;
    arcPath2.addArc(centreX - radius,
                    centreY - radius,
                    radius * 2,
                    radius * 2,
                    juce::MathConstants<float>::pi * 1.25f,
                    juce::MathConstants<float>::pi * 1.75f,
                    true);
    g.strokePath(arcPath2, strokeType);

    radius *= 0.5f;
    g.setColour(Colours::darkgrey);
    g.fillEllipse(centreX - radius, centreY - radius, radius * 2, radius * 2);

    radius *= 0.2f;
    g.setColour(colour);
    g.fillEllipse(centreX - radius, centreY - radius, radius * 2, radius * 2);
}