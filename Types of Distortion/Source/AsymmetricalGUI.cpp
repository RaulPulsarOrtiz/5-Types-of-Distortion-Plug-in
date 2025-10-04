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

    asymVariableText.setText("Asymmetric Value", dontSendNotification);
    asymVariableText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(asymVariableText);
    asymVariableText.setVisible(false);
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
  //  auto area = guiPosition.getWorkingArea();
  //  auto knobsArea = guiPosition.getKnobsArea();
  //
  //  asymVariableSldr.setBounds(knobsArea.removeFromLeft(150));
  //  asymVariableSldr.setSize(100, 100);
  //
  //  Rectangle <int> asymmetricSldrPos = asymVariableSldr.getBounds();
  //  int posX = asymmetricSldrPos.getCentreX();
  //  int posY = asymmetricSldrPos.getCentreY();
  //
  //  asymVariableText.setBounds((posX - 60), (posY + 50), 115, 15);
    auto area = getLocalBounds();
    auto asymmetricalGUIPos = area.removeFromBottom(100).withSizeKeepingCentre(100, 100);
    asymVariableSldr.setBounds(asymmetricalGUIPos);
    
}

void AsymmetricalGUI::setAsymmetrical(AsymmetricalProcessor* asymmetricProcessptr)
{
    asymmetricProcessPtr = asymmetricProcessptr;
}