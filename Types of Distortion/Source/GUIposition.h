/*
  ==============================================================================

    GUIposition.h
    Created: 15 Jan 2023 2:21:18pm
    Author:  Raul

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

class GUIposition : public Component
{
public:
    /** Rectangles to divide the whole Plug-in area in smaller areas to place the different components*/
   
    /*@return the whole area minus some borders at the edges*/
    void paint(juce::Graphics& g) override;
    juce::Rectangle<int> getInnerArea();
    juce::Rectangle<int> getInputMeterArea(int channel);
    juce::Rectangle<int> getOutputMeterArea(int channel);
    juce::Rectangle<int> getLeftComponentArea();
    juce::Rectangle<int> getRightComponentArea();
    juce::Point<int> getCentre();
private:
  //  juce::Rectangle<int> halfLeftArea, leftQuarterArea, rightQuarterArea;
};