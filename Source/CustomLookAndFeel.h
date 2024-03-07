#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    explicit CustomLookAndFeel(const Colour &_colour);

    CustomLookAndFeel(const Colour &_colour1, const Colour &_colour2);

    void drawLinearSlider(Graphics &g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          Slider::SliderStyle style, Slider &slider) override;

    void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
                          const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &) override;

    void drawButtonBackground(juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override;

private:
    Colour colour;

    Colour colour1, colour2;
};