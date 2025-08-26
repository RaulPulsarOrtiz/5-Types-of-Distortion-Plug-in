/*
  ==============================================================================

    GUIposition.cpp
    Created: 15 Jan 2023 2:21:18pm
    Author:  Raul

  ==============================================================================
*/

#include "GUIposition.h"

//auto totalArea = getLocalBounds();
//auto innerArea = totalArea.reduced(50);
//auto halfLeftArea = innerArea.withWidth(innerArea.getWidth() / 2);
//auto leftQuarterArea = innerArea.withWidth(innerArea.getWidth() / 4);
//auto rightQuarterArea = innerArea.removeFromRight(innerArea.getWidth() / 4);
//auto inputMeterArea = leftQuarterArea.withWidth(leftQuarterArea.getWidth() - 50);
//auto outputMeterArea = rightQuarterArea.withWidth(rightQuarterArea.getWidth() - 50).withX(rightQuarterArea.getX() + 50);
//auto leftComponentArea = halfLeftArea.removeFromRight(leftQuarterArea.getWidth());
//auto rightComponentArea = innerArea.removeFromRight(rightQuarterArea.getWidth());
//auto middlePointX = innerArea.getCentreX();
//auto middlePointY = innerArea.getCentreY();


juce::Rectangle<int> GUIposition::getInnerArea()
{
    auto totalArea = getLocalBounds();
    auto innerArea = totalArea.reduced(50);

    return innerArea;
}

juce::Rectangle<int> GUIposition::getInputMeterArea(int channel)
{
    auto totalArea = getLocalBounds();
    auto innerArea = totalArea.reduced(50);
    auto halfLeftArea = innerArea.withWidth(innerArea.getWidth() / 2);
    auto leftQuarterArea = innerArea.withWidth(innerArea.getWidth() / 4);
    auto inputMeterArea = leftQuarterArea.withWidth(leftQuarterArea.getWidth() - 50);
    auto inputMeterAreaL = inputMeterArea.withWidth(inputMeterArea.getWidth() / 2);
    auto inputMeterAreaR = inputMeterArea.removeFromRight(inputMeterAreaL.getWidth());
   
    if (channel == 0)
    {
        return inputMeterAreaL;
    }
    else if (channel == 1)
    {
        return inputMeterAreaR;
    }
    
}

juce::Rectangle<int> GUIposition::getOutputMeterArea(int channel)
{
    auto totalArea = getLocalBounds();
    auto innerArea = totalArea.reduced(50);
    auto rightQuarterArea = innerArea.removeFromRight(innerArea.getWidth() / 4);
    auto outputMeterArea = rightQuarterArea.withWidth(rightQuarterArea.getWidth() - 50).withX(rightQuarterArea.getX() + 50);
    auto outputMeterAreaL = outputMeterArea.withWidth(outputMeterArea.getWidth() / 2);
    auto outputMeterAreaR = outputMeterArea.removeFromRight(outputMeterAreaL.getWidth());

    if (channel == 0)
    {
        return outputMeterAreaL;
    }
    else if (channel == 1)
    {
        return outputMeterAreaR;
    }
}

juce::Rectangle<int> GUIposition::getLeftComponentArea()
{
    auto totalArea = getLocalBounds();
    auto innerArea = totalArea.reduced(50);
    auto halfLeftArea = innerArea.withWidth(innerArea.getWidth() / 2);
    auto leftQuarterArea = innerArea.withWidth(innerArea.getWidth() / 4);
    auto leftComponentArea = halfLeftArea.removeFromRight(leftQuarterArea.getWidth());
    return leftComponentArea;
}

juce::Rectangle<int> GUIposition::getRightComponentArea()
{
    auto totalArea = getLocalBounds();
    auto innerArea = totalArea.reduced(50);
    auto rightQuarterArea = innerArea.removeFromRight(innerArea.getWidth() / 4);
    auto rightComponentArea = innerArea.removeFromRight(innerArea.getWidth() / 2);
    rightComponentArea.removeFromLeft(rightQuarterArea.getWidth());
    return rightComponentArea;
}

juce::Point<int> GUIposition::getCentre()
{
    auto totalArea = getLocalBounds();
    auto innerArea = totalArea.reduced(50);
    auto centrePoint = innerArea.getCentre();
    return centrePoint;
}


void GUIposition::paint(juce::Graphics& g) //Only to check
{
    g.setColour(juce::Colours::yellow);
    g.drawRect(getInputMeterArea(0));
    g.drawRect(getOutputMeterArea(0));

    g.setColour(juce::Colours::darkred);
    g.drawRect(getInputMeterArea(1));
    g.drawRect(getOutputMeterArea(1));

    g.setColour(juce::Colours::aliceblue);
    g.drawRect(getLeftComponentArea());
    g.drawRect(getRightComponentArea());
}