/////////////////////// I wrote the following code //////////////////////

#pragma once

#include <JuceHeader.h>

/** CustomLookAndFeel is a custom LookAndFeel class that inherits from juce::LookAndFeel_V4.
 *  It is used to customize the appearance of the GUI components.
 *  It customizes the following components:
 *  - Linear Vertical Slider
 *  - Linear Horizontal Slider
 *  - Linear Bar Slider
 *  - Rotary Slider
 *  - Button (TextButton especially)
 */
class CustomLookAndFeel
        : public juce::LookAndFeel_V4 {
public:
    //==============================================================================
    /** Creates a CustomLookAndFeel with one single colour.
     *  @param _colour The colour to be used for styling the components.
     */
    explicit CustomLookAndFeel(const Colour &_colour);


    /** Creates a CustomLookAndFeel with two colours.
     *  @param _colour1 The first colour to be used for styling the components.
     *  @param _colour2 The second colour to be used for styling the components.
     */
    CustomLookAndFeel(const Colour &_colour1, const Colour &_colour2);

    //==============================================================================
    /** Draws a linear slider (including linear vertical, linear horizontal, and linear bar sliders).
     *  @param g The Graphics object to draw on.
     *  @param x The x-coordinate of the top-left corner of the component.
     *  @param y The y-coordinate of the top-left corner of the component.
     *  @param width The width of the component.
     *  @param height The height of the component.
     *  @param sliderPos The current position of the slider thumb.
     *  @param minSliderPos The minimum position of the slider thumb.
     *  @param maxSliderPos The maximum position of the slider thumb.
     *  @param style The style of the slider.
     *  @param slider The slider to be drawn.
     */
    void drawLinearSlider(Graphics &g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          Slider::SliderStyle style, Slider &slider) override;

    /** Draws a rotary slider.
     *  @param g The Graphics object to draw on.
     *  @param x The x-coordinate of the top-left corner of the component.
     *  @param y The y-coordinate of the top-left corner of the component.
     *  @param width The width of the component.
     *  @param height The height of the component.
     *  @param sliderPos The current position of the slider thumb.
     *  @param rotaryStartAngle The start angle of the rotary slider.
     *  @param rotaryEndAngle The end angle of the rotary slider.
     *  @param slider The slider to be drawn.
     */
    void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle, juce::Slider &) override;

    /** Draws the background of a button.
     *  @param g The Graphics object to draw on.
     *  @param button The button to be drawn.
     *  @param backgroundColour The background colour of the button.
     *  @param isMouseOverButton A boolean value indicating whether the mouse is over the button.
     *  @param isButtonDown A boolean value indicating whether the button is being pressed.
     */
    void drawButtonBackground(juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override;

    /** Returns the font to be used for drawing the text on a button.
     *  @param button The button to be drawn.
     *  @param buttonHeight The height of the button.
     *  @return The font to be used for drawing the text on the button.
     */
    Font getTextButtonFont(TextButton &, int buttonHeight) override;

private:
    //==============================================================================
    Colour colour;
    Colour colour1, colour2;
};

//////////////////////////// End of my code ////////////////////////////