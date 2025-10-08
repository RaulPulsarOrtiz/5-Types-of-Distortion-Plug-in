/*
  ==============================================================================

    CustomSliders.cpp
    Created: 12 Sep 2025 6:38:38pm
    Author:  Raul

  ==============================================================================
*/

#include "CustomSliders.h"

FilmStripSlider::FilmStripSlider(juce::Image* _knobStrip, int _frameCount, int _frameSize, bool _isVerticalStrip) {
    knobStrip = _knobStrip;
    frameSize = _frameSize;
    frameCount = _frameCount;
    isVerticalStrip = _isVerticalStrip;
}

void FilmStripSlider::drawFrame(juce::Graphics& g, int x, int y, int width, int height, juce::Slider& slider) {
   
    const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
    int pos = (int)ceil(fractRotation * ((double)frameCount - 1.0)); // current index from 0 ---> nFrames-1

    slider.getRange();

    if (width != height) /* scale */
    {
        x = (width / 2) - (height / 2);
        width = height;
    }

    if (isVerticalStrip)
    {
        g.drawImage(*knobStrip, x, y, width, height, 0, (int)(pos * frameSize), frameSize, frameSize, false);
    }
    else
    {
        g.drawImage(*knobStrip, x, y, width, height, (int)(pos * frameSize), 0, frameSize, frameSize, false);
    }
}

void LookAndFeelDistortion::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{

    FilmStripSlider knobDisSteps = FilmStripSlider(&knobDistort7Strip, 7, 83, true);
    knobDisSteps.drawFrame(g, x, y, width, height, slider);
}

void LookAndFeel22Steps::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{

    FilmStripSlider knob22Steps = FilmStripSlider(&knobDistort22Strip, 20, 83, true);
    knob22Steps.drawFrame(g, x, y, width, height, slider);
}