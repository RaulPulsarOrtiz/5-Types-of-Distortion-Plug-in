/*
  ==============================================================================

    AsymmetricalGUI.cpp
    Created: 6 Jan 2023 2:42:24pm
    Author:  Raul

  ==============================================================================
*/

#include "AsymmetricalGUI.h"

AsymmetricalGUI::AsymmetricalGUI()
{
    asymVariableSldr.setSliderStyle(Slider::Rotary);
    asymVariableSldr.setRange(0.5f, 1.5f, 0.1f);
    asymVariableSldr.setValue(1.f);
    asymVariableSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 15);
    asymVariableSldr.setLookAndFeel(&twentyTwoStepsLookAndFeel);
    asymVariableSldr.addListener(this);
    addAndMakeVisible(asymVariableSldr);
    asymVariableSldr.setVisible(true);
}

AsymmetricalGUI::~AsymmetricalGUI()
{
    asymVariableSldr.setLookAndFeel(nullptr);
}

void AsymmetricalGUI::sliderValueChanged(Slider* slider)
{
     if (slider == &asymVariableSldr)
    {
         asymmetricProcessPtr->setAsymVariable(asymVariableSldr.getValue());
    }
}

void AsymmetricalGUI::resized()
{
    auto area = getLocalBounds();
    auto asymmetricalGUIPos = area.removeFromBottom(100).withSizeKeepingCentre(100, 100);
    asymVariableSldr.setBounds(asymmetricalGUIPos);
    
}

void AsymmetricalGUI::setAsymmetrical(AsymmetricalProcessor* asymmetricProcessptr)
{
    asymmetricProcessPtr = asymmetricProcessptr;
}