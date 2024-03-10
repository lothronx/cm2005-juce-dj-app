/////////////////////// I wrote the following code //////////////////////

#include "CustomLookAndFeel.h"

//==============================================================================
CustomLookAndFeel::CustomLookAndFeel(const Colour &_colour)
        : colour{_colour} {}


CustomLookAndFeel::CustomLookAndFeel(const Colour &_colour1, const Colour &_colour2)
        : colour1{_colour1}
        , colour2{_colour2} {}

//==============================================================================
void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height,
                                         float sliderPos, float minSliderPos, float maxSliderPos,
                                         Slider::SliderStyle style, Slider &slider) {
    auto floatX = static_cast<float>(x);
    auto floatY = static_cast<float>(y);
    auto floatWidth = static_cast<float>(width);
    auto floatHeight = static_cast<float>(height);
    //==============================================================================
    // Linear Vertical Slider
    if (style == juce::Slider::LinearVertical) {
        // The tick marks
        // Draw 11 tick marks that are evenly spaced along the slider, dividing it into 10 equal parts.
        // The first, last, and middle tick marks are drawn longer and thicker than the rest.
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

        // The slider background
        // Draw a grey bar that is 10 pixels wide and spans the entire height of the component.
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(floatX + (floatWidth / 2) - 5, floatY, 10.0f,
                   floatHeight);

        // The slider track
        // Draw a coloured bar that starts from the middle position of the slider
        g.setColour(colour);
        float midPos = floatY + floatHeight / 2;
        g.fillRect(floatX + (floatWidth / 2) - 5, sliderPos, 10.0f, midPos - sliderPos);

        // The slider thumb
        // Draw a white rounded rectangle.
        g.setColour(juce::Colours::white);
        g.fillRoundedRectangle(floatX + 7, sliderPos - 8, floatWidth - 14, 16.0f,
                               4.0f);

    }

    //==============================================================================
    // Linear Horizontal Slider
    if (style == juce::Slider::LinearHorizontal) {
        // The tick marks
        // Draw 11 tick marks that are evenly spaced along the slider, dividing it into 10 equal parts.
        // The first, last, and middle tick marks are drawn longer and thicker than the rest.
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

        // The slider background
        // Draw a grey bar that is 10 pixels tall and spans the entire width of the component.
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(floatX, floatY + (floatHeight / 2) - 5,
                   floatWidth, 10.0f);

        // The slider track
        // Based on the current position of the slider thumb,
        // colour the left side of the slider track with colour2 and the right side with colour1,
        // so that, for example, when the thumb moves closer to the right (Deck2),
        // colour2 will be longer and colour1 will be shorter.
        g.setColour(colour2);
        g.fillRect(floatX, floatY + (floatHeight / 2) - 5, jmin(sliderPos, floatWidth), 10.0f);
        g.setColour(colour1);
        g.fillRect(sliderPos, floatY + (floatHeight / 2) - 5, floatX + floatWidth - sliderPos, 10.0f);

        // The slider thumb
        // Draw a white rounded rectangle.
        g.setColour(juce::Colours::white);
        g.fillRoundedRectangle(sliderPos - 8, floatY + (floatHeight / 2) - 20, 16, 40,
                               4);
    }

    //==============================================================================
    // Linear Bar Slider
    // This is for the position slider that overlaps the waveform display
    if (style == juce::Slider::LinearBar) {
        // The slider background is transparent

        // The slider track
        // Draw a semi-transparent black bar
        g.setColour(Colours::black.withAlpha(0.3f));
        g.fillRect(floatX, floatY, sliderPos - floatX, floatHeight);

        // The slider thumb
        // Draw a white line indicating the current position
        g.setColour(Colours::white);
        g.drawLine(sliderPos, floatY, sliderPos, floatY + floatHeight, 1.0f);
    }
}

//==============================================================================
// Rotary Slider
void CustomLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos,
                                         const float rotaryStartAngle, const float rotaryEndAngle, Slider &) {

    auto radius = (float) juce::jmin(width / 2, height / 2) - 10.0f;
    auto centreX = (float) x + (float) width / 2;
    auto centreY = (float) y + (float) height / 2;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    // The current angle of the slider thumb
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // The knob
    // Draw a colored solid circle
    g.setColour(colour);
    g.fillEllipse(rx, ry, rw, rw);

    // The indicator
    // Draw a white line indicating the current position
    g.setColour(juce::Colours::white.withAlpha(0.9f));
    juce::Path pointer;
    pointer.addRoundedRectangle(-3.0f, -radius, 6.0f, radius * 0.6f, 1.0f);
    pointer.applyTransform(juce::AffineTransform::rotation(angle)
                                   .translated(centreX, centreY));
    g.fillPath(pointer);

    // The track
    // Draw a grey arc that spans the entire range of the rotary slider
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

    // The coloured track (progress arc)
    // Draw a coloured arc that starts from the middle position of the rotary slider
    g.setColour(colour);
    juce::Path trackColored;
    trackColored.addArc(rx - 6,
                        ry - 6,
                        rw + 12,
                        rw + 12,
                        (rotaryStartAngle + rotaryEndAngle) / 2,
                        angle,
                        true);
    g.strokePath(trackColored, strokeType);
}

//==============================================================================
// Button
void
CustomLookAndFeel::drawButtonBackground(juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour,
                                        bool isMouseOverButton, bool isButtonDown) {

    // If the button is toggled on, the background color will be the user-defined colour.
    // If the button is toggled off, the background color will be dark grey.
    auto bgColour = button.getToggleState() ? colour : Colours::darkgrey;

    // If the button is being pressed or the mouse is over the button, make the background color brighter.
    if (isButtonDown || isMouseOverButton)
        bgColour = bgColour.brighter();

    // Draw a rounded rectangle with the background colour determined above.
    g.setColour(bgColour);
    auto bounds = button.getLocalBounds().toFloat().reduced(1.0f);
    g.fillRoundedRectangle(bounds, 10.0f);
}

// Set the text button font size to 20
Font CustomLookAndFeel::getTextButtonFont(juce::TextButton &, int buttonHeight) {
    return {20.0f};
}

//////////////////////////// End of my code ////////////////////////////