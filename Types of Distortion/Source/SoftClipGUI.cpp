/*
  ==============================================================================

    SoftClipGUI.cpp
    Created: 6 Jan 2023 12:55:33pm
    Author:  Raul

  ==============================================================================
*/

#include "SoftClipGUI.h"

SoftClipGUI::SoftClipGUI()
{
    softCurveSldr.setSliderStyle(Slider::Rotary);
    softCurveSldr.setRange(10, 10000);
    softCurveSldr.setValue(10);
    softCurveSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 15);
    softCurveSldr.addListener(this);
    addAndMakeVisible(softCurveSldr);
    softCurveSldr.setVisible(true);

    softCurveText.setText("Curve Value", dontSendNotification);
    softCurveText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(softCurveText);
    softCurveText.setVisible(false);
   }

void SoftClipGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &softCurveSldr)
    {
        softClipProcessPtr->setSoftCurve(softCurveSldr.getValue());
    }

}

void SoftClipGUI::resized()
{
  //  guiPosition.setBounds(getLocalBounds());
  
        auto area = getLocalBounds();

        // now position the slider within SoftClipGUI
        auto softCurveSldrPos = area.removeFromTop(120).withSizeKeepingCentre(100, 100);
        softCurveSldr.setBounds(softCurveSldrPos);

  //  Rectangle <int> softCurveSldrPos = softCurveSldr.getBounds();
  //  int posX = softCurveSldrPos.getCentreX();
  //  int posY = softCurveSldrPos.getCentreY();
  //
  //  softCurveText.setBounds((posX - 45), (posY + 50), 80, 15);
   // clipGainValuesText.setBounds((posX - 32), (posY + 70), 100, 15);
}

void SoftClipGUI::setSoftClip(SoftClipProcessor* softClipPorcessorptr)
{
    softClipProcessPtr = softClipPorcessorptr;    
}