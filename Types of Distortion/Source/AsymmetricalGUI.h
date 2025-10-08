/*
  ==============================================================================

    AsymmetricalGUI.h
    Created: 6 Jan 2023 2:42:24pm
    Author:  Raul

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AsymmetricalProcessor.h"
#include "GUIposition.h"
#include "CustomSliders.h"

class AsymmetricalGUI : public Component,
                        public Slider::Listener
{
public:
    AsymmetricalGUI();
    ~AsymmetricalGUI();
    void sliderValueChanged(Slider* slider) override;
    void resized() override;
    Slider asymVariableSldr;
    void setAsymmetrical(AsymmetricalProcessor*);

private:
    /** Reference to the AsymmetricalProcessor class through a pointer to access and control AsymmetricalProcessor class member functions */
    AsymmetricalProcessor* asymmetricProcessPtr { nullptr };
    GUIposition guiPosition;
    LookAndFeel22Steps twentyTwoStepsLookAndFeel;
};