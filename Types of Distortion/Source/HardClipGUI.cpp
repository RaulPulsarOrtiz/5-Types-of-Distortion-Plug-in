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
    clippingGainSldr.setRange(1.f, 7.94f, 1.12f); //This is linear but when being transform in dB it will go from 0db to +18 dB
    clippingGainSldr.setValue(1.f);
    clippingGainSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 40, 15);
    clippingGainSldr.setTextValueSuffix("dB");
    clippingGainSldr.setLookAndFeel(&lookAndFeelDistortion);
    clippingGainSldr.addListener(this);
    addAndMakeVisible(clippingGainSldr);
}

HardClipGUI::~HardClipGUI()
{
    clippingGainSldr.setLookAndFeel(nullptr);
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
    sliderWidth = 100;
    sliderHeight = 100;

    auto area = getLocalBounds();//.withSizeKeepingCentre(100, 100);
    clippingGainSldr.setBounds(area);
 }

void HardClipGUI::setHardClip(HardClipProcessor* hardClipPorcessorptr)
{
    hardClipProcessPtr = hardClipPorcessorptr;
}