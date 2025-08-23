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

juce::Rectangle<int> GUIposition::getInputMeterArea()
{
    auto totalArea = getLocalBounds();
    auto innerArea = totalArea.reduced(50);
    auto halfLeftArea = innerArea.withWidth(innerArea.getWidth() / 2);
    auto leftQuarterArea = innerArea.withWidth(innerArea.getWidth() / 4);
    auto inputMeterArea = leftQuarterArea.withWidth(leftQuarterArea.getWidth() - 50);
    return inputMeterArea;
}

juce::Rectangle<int> GUIposition::getOutputMeterArea()
{
    auto totalArea = getLocalBounds();
    auto innerArea = totalArea.reduced(50);
    auto rightQuarterArea = innerArea.removeFromRight(innerArea.getWidth() / 4);
    auto outputMeterArea = rightQuarterArea.withWidth(rightQuarterArea.getWidth() - 50).withX(rightQuarterArea.getX() + 50);
    return outputMeterArea;
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

void GUIposition::paint(juce::Graphics& g) //Only to check
{
    g.setColour(juce::Colours::yellow);
    g.drawRect(getInputMeterArea());
    g.drawRect(getOutputMeterArea());
   
    g.setColour(juce::Colours::aliceblue);
    g.drawRect(getLeftComponentArea());
    g.drawRect(getRightComponentArea());
}