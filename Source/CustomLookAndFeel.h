#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    explicit CustomLookAndFeel(const Colour& _colour);

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          Slider::SliderStyle style, Slider& slider) override;

private:
    Colour colour;
};