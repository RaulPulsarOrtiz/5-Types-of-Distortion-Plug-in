/*
  ==============================================================================

    HardClipGUI.cpp
    Created: 6 Jan 2023 11:29:09am
    Author:  Raul

  ==============================================================================
*/

#include "HardClipGUI.h"

HardClipGUI::HardClipGUI()
{
    clippingGainSldr.setSliderStyle(Slider::Rotary);
    //setTextBoxStyle()
    clippingGainSldr.setRange(1, 10, 1);
    clippingGainSldr.setValue(1);
    clippingGainSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 40, 15);
    clippingGainSldr.addListener(this);
    addAndMakeVisible(clippingGainSldr);

    clipGainText.setText("Clipping Gain", dontSendNotification);
   // clipGainText.setJustificationType(juce::Justification::centredTop);
    clipGainText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(clipGainText);
   
    clipGainValuesText.setText("1    -    10", dontSendNotification);
    addAndMakeVisible(clipGainValuesText);
}

void HardClipGUI::sliderValueChanged(Slider* slider)
{
    {
        if (slider == &clippingGainSldr)
        {
            hardClipProcessPtr->setClippingGain(clippingGainSldr.getValue());
        }
    }
}

void HardClipGUI::resized()
{
   // auto area = guiPosition.getWorkingArea();
   // auto knobsArea = guiPosition.getKnobsArea();
   //
   // clippingGainSldr.setBounds(knobsArea.removeFromLeft(150));
   // clippingGainSldr.setSize(100, 100);
   //
   // Rectangle <int> clipGainSldrPos = clippingGainSldr.getBounds();
   // int posX = clipGainSldrPos.getCentreX();
   // int posY = clipGainSldrPos.getCentreY();
   //
   // clipGainText.setBounds((posX - 50), (posY + 50), 100, 15);
   // clipGainValuesText.setBounds((posX - 32), (posY + 70), 100, 15);

    sliderWidth = 100;
    sliderHeight = 100;

    auto area = getLocalBounds();
    clippingGainSldr.setBounds(area);
 }

void HardClipGUI::setHardClip(HardClipProcessor* hardClipPorcessorptr)
{
    hardClipProcessPtr = hardClipPorcessorptr;
}