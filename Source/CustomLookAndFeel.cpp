#include "CustomLookAndFeel.h"


CustomLookAndFeel::CustomLookAndFeel(const Colour &_colour)
        : colour{_colour} {}


CustomLookAndFeel::CustomLookAndFeel(const Colour &_colour1, const Colour &_colour2)
        : colour1{_colour1}, colour2{_colour2} {}


void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height,
                                         float sliderPos, float minSliderPos, float maxSliderPos,
                                         Slider::SliderStyle style, Slider &slider) {
    auto floatX = static_cast<float>(x);
    auto floatY = static_cast<float>(y);
    auto floatWidth = static_cast<float>(width);
    auto floatHeight = static_cast<float>(height);

    if (style == juce::Slider::LinearVertical) {
        g.setColour(juce::Colours::grey.withAlpha(0.8f));
        const int numTicks = 11;
        const float spacing = floatHeight / (numTicks - 1);
        for (int i = 0; i < numTicks; ++i) {
            float tickPosition = floatY + static_cast<float>(i) * spacing;
            if (i == 0 || i == numTicks - 1 || i == numTicks / 2)
                g.drawLine(floatX + (floatWidth / 2) - 18, tickPosition,
                           floatX + (floatWidth / 2) + 18, tickPosition,
                           1.0f);
            else
                g.drawLine(floatX + (floatWidth / 2) - 12, tickPosition,
                           floatX + (floatWidth / 2) + 12, tickPosition,
                           0.5f);
        }

        g.setColour(juce::Colours::darkgrey);
        g.fillRect(floatX + (floatWidth / 2) - 5, floatY, 10.0f,
                   floatHeight);

        g.setColour(colour);
        float midPos = floatY + floatHeight / 2;
        g.fillRect(floatX + (floatWidth / 2) - 5, sliderPos, 10.0f, midPos - sliderPos);

        g.setColour(juce::Colours::white);
        g.fillRoundedRectangle(floatX + 7, sliderPos - 8, floatWidth - 14, 16.0f,
                               4.0f);

    }

    if (style == juce::Slider::LinearHorizontal) {
        g.setColour(juce::Colours::grey.withAlpha(0.8f));
        const int numTicks = 11;
        const float spacing = floatWidth / (numTicks - 1);
        for (int i = 0; i < numTicks; ++i) {
            float tickPosition = floatX + static_cast<float>(i) * spacing;
            if (i == 0 || i == numTicks - 1 || i == numTicks / 2)
                g.drawLine(tickPosition, floatY + (floatHeight / 2) - 18,
                           tickPosition, floatY + (floatHeight / 2) + 18,
                           1.0f);
            else
                g.drawLine(tickPosition, floatY + (floatHeight / 2) - 12,
                           tickPosition, floatY + (floatHeight / 2) + 12,
                           0.5f);
        }

        g.setColour(juce::Colours::darkgrey);
        g.fillRect(floatX, floatY + (floatHeight / 2) - 5,
                   floatWidth, 10.0f);

        g.setColour(colour2);
        g.fillRect(floatX, floatY + (floatHeight / 2) - 5, jmin(sliderPos, floatWidth), 10.0f);
        g.setColour(colour1);
        g.fillRect(sliderPos, floatY + (floatHeight / 2) - 5, floatX + floatWidth - sliderPos, 10.0f);


        g.setColour(juce::Colours::white);
        g.fillRoundedRectangle(sliderPos - 8, floatY + (floatHeight / 2) - 20, 16, 40,
                               4);
    }

    if (style == juce::Slider::LinearBar) {
        g.setColour(Colours::black.withAlpha(0.3f));
        g.fillRect(floatX, floatY, sliderPos - floatX, floatHeight);
        g.setColour(Colours::white);
        g.drawLine(sliderPos, floatY, sliderPos, floatY + floatHeight, 1.0f);
    }
}

void CustomLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos,
                                         const float rotaryStartAngle, const float rotaryEndAngle, Slider &) {
    auto radius = (float) juce::jmin(width / 2, height / 2) - 10.0f;
    auto centreX = (float) x + (float) width / 2;
    auto centreY = (float) y + (float) height / 2;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    g.setColour(colour);
    g.fillEllipse(rx, ry, rw, rw);

    g.setColour(juce::Colours::white.withAlpha(0.9f));
    juce::Path pointer;
    pointer.addRoundedRectangle(-3.0f, -radius, 6.0f, radius * 0.6f, 1.0f);
    pointer.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
    g.fillPath(pointer);

    g.setColour(Colours::grey.withAlpha(0.5f));
    juce::PathStrokeType strokeType(5.0f);
    juce::Path track;
    track.addArc(rx - 6,
                 ry - 6,
                 rw + 12,
                 rw + 12,
                 rotaryStartAngle,
                 rotaryEndAngle,
                 true);
    g.strokePath(track, strokeType);

    g.setColour(colour);
    juce::Path trackColored;
    trackColored.addArc(rx - 6,
                        ry - 6,
                        rw + 12,
                        rw + 12,
                        (rotaryStartAngle + rotaryEndAngle) / 2,
                        rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle),
                        true);
    g.strokePath(trackColored, strokeType);
}

void
CustomLookAndFeel::drawButtonBackground(juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour,
                                        bool isMouseOverButton, bool isButtonDown) {

    auto colours = button.getToggleState() ? colour : Colours::darkgrey;

    if (isButtonDown || isMouseOverButton)
        colours = colours.brighter();

    g.setColour(colours);

    auto bounds = button.getLocalBounds().toFloat().reduced(1.0f);
    g.fillRoundedRectangle(bounds, 10.0f);
}

Font CustomLookAndFeel::getTextButtonFont(juce::TextButton &, int buttonHeight) {
    return Font(20.0f);
}
