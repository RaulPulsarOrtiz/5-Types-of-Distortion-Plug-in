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
    softCurveSldr.setRange(0.1, 10, 0.1);
   // softCurveSldr.setValue(10);
    softCurveSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 15);
    softCurveSldr.setLookAndFeel(&twentyTwoStepsLookAndFeel);
    softCurveSldr.addListener(this);
    addAndMakeVisible(softCurveSldr);
    softCurveSldr.setVisible(true);
}

SoftClipGUI::~SoftClipGUI()
{
    softCurveSldr.setLookAndFeel(nullptr);
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
}

void SoftClipGUI::setSoftClip(SoftClipProcessor* softClipPorcessorptr)
{
    softClipProcessPtr = softClipPorcessorptr;    
}