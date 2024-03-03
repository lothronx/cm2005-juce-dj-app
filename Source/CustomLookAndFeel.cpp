#include "CustomLookAndFeel.h"


CustomLookAndFeel::CustomLookAndFeel(const Colour &_colour)
        : colour{_colour} {}


void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height,
                                         float sliderPos, float minSliderPos, float maxSliderPos,
                                         Slider::SliderStyle style, Slider &slider) {
    auto floatX = static_cast<float>(x);
    auto floatY = static_cast<float>(y);
    auto floatWidth = static_cast<float>(width);
    auto floatHeight = static_cast<float>(height);

    if (style == juce::Slider::LinearVertical) {
        g.setColour(juce::Colours::grey);
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

        g.setColour(Colours::darkgrey);
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