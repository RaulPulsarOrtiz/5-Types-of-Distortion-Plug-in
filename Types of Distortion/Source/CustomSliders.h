/*
  ==============================================================================

    CustomSliders.h
    Created: 12 Sep 2025 6:38:38pm
    Author:  Raul

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/** Class to take the knob images strip */

class FilmStripSlider
{
public:
    FilmStripSlider(juce::Image* _knobStrip, int _frameCount, int _frameSize, bool _isVerticalStrip);
    ~FilmStripSlider() {}

    /** This function workout the minimum and maximum values of the slider and it shows the corresponding frame of the image strip based on the current value */
    void drawFrame(juce::Graphics& g, int x, int y, int width, int height, juce::Slider& slider);

private:
    /** This image is a strip of the different images of the slider with every different value  */
    juce::Image* knobStrip = nullptr;

    /** Number of frame values on the slider */
    int frameCount = 0;

    /** Width of the image */
    int frameSize = 0;

    /** If that image is vertical or horizontal */
    bool isVerticalStrip = true;
};

/** Custom LookAndFeel class for delayTime and Feedback sliders */
class LookAndFeelDistortion : public juce::LookAndFeel_V4
{
public:
    LookAndFeelDistortion() //On the constructor we set up some default colours for different parts of the GUI
    {

    }
    ~LookAndFeelDistortion() {}

    /** Get Image (binary data) from memory
    * @param BinaryData::BinaryData::attackKnob_png is the Binary Data of image for the Attack and Release sliders
    * @param BinaryData::attackKnob_pngSize is the size of the frame of each slider image in the strip
    */
    Image knobDistort7Strip = ImageCache::getFromMemory(BinaryData::Distortion7Steps_png, BinaryData::Distortion7Steps_pngSize);

    /** This funcion draws the slider image for the delayTime and feedback, instead of drawing a standard JUCE slider */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle,
        const float rotaryEndAngle, juce::Slider&) override; // (x, y, width, height) are passing from the slider's resize() function. 
                                                             //sliderPost is where the slider is from 0 to 1.
                                                             // rotaryAngle is the angle in radiants from the center of the slider to the start position or to the end position
};

/** Custom LookAndFeel class for delayTime and Feedback sliders */
class LookAndFeel22Steps : public juce::LookAndFeel_V4
{
public:
    LookAndFeel22Steps() //On the constructor we set up some default colours for different parts of the GUI
    {

    }
    ~LookAndFeel22Steps() {}

    /** Get Image (binary data) from memory
    * @param BinaryData::BinaryData::attackKnob_png is the Binary Data of image for the Attack and Release sliders
    * @param BinaryData::attackKnob_pngSize is the size of the frame of each slider image in the strip
    */
    Image knobDistort22Strip = ImageCache::getFromMemory(BinaryData::OutputGain221_png, BinaryData::OutputGain221_pngSize);

    /** This funcion draws the slider image for the delayTime and feedback, instead of drawing a standard JUCE slider */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle,
        const float rotaryEndAngle, juce::Slider&) override; // (x, y, width, height) are passing from the slider's resize() function. 
                                                             //sliderPost is where the slider is from 0 to 1.
                                                             // rotaryAngle is the angle in radiants from the center of the slider to the start position or to the end position
};