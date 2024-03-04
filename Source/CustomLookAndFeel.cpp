#include "CustomLookAndFeel.h"


CustomLookAndFeel::CustomLookAndFeel(const Colour &_colour)
        : colour{_colour} {
    setColour(TextButton::buttonColourId, juce::Colours::darkgrey);
}


void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height,
                                         float sliderPos, float minSliderPos, float maxSliderPos,
                                         Slider::SliderStyle style, Slider &slider) {
    auto floatX = static_cast<float>(x);
    auto floatY = static_cast<float>(y);
    auto floatWidth = static_cast<float>(width);
    auto floatHeight = static_cast<float>(height);

    if (style == juce::Slider::LinearVertical) {
        g.setColour(juce::Colours::lightgrey);
        const int numTicks = 11;
        const float spacing = floatHeight / (numTicks - 1);
        for (int i = 0; i < numTicks; ++i) {
            float tickPosition = floatY + static_cast<float>(i) * spacing;
            if (i == 0 || i == numTicks - 1 || i == numTicks / 2)
                g.drawLine(floatX + 5, tickPosition,
                           floatX + floatWidth - 5, tickPosition,
                           1.0f);
            else
                g.drawLine(floatX + 8, tickPosition,
                           floatX + floatWidth - 8, tickPosition,
                           0.5f);
        }

        g.setColour(juce::Colours::darkgrey);
        g.fillRect(floatX + (floatWidth / 2) - 5, floatY, 10.0f,
                   floatHeight);

        g.setColour(colour.withAlpha(0.6f));
        float midPos = floatY + floatHeight / 2;
        g.fillRect(floatX + (floatWidth / 2) - 5, sliderPos, 10.0f, midPos - sliderPos);

        g.setColour(colour);
        g.fillRoundedRectangle(floatX + 5, sliderPos - 5, floatWidth - 10, 10.0f,
                               2.0f); // Rounded rectangle for a thumb

    }

    if (style == juce::Slider::LinearBar) {
        g.setColour (Colours::black.withAlpha(0.3f));
        g.fillRect (floatX, floatY, sliderPos -floatX, floatHeight);
        g.setColour(Colours::white);
        g.drawLine(sliderPos, floatY,sliderPos, floatY + floatHeight,1.0f);
    }
}

void CustomLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos,
                                         const float rotaryStartAngle, const float rotaryEndAngle, Slider &) {

    auto radius = (float) juce::jmin (width / 2, height / 2) - 10.0f;
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    g.setColour (colour);
    g.fillEllipse (rx, ry, rw, rw);
    g.setColour (colour);
    g.drawEllipse (rx - 4, ry - 4, rw + 8, rw + 8, 3.0f);

    juce::Path p;
    auto pointerLength = radius * 0.6f;
    auto pointerThickness = 4.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
    g.setColour (juce::Colours::white.withAlpha(0.9f));
    g.fillPath (p);



}
