/*
  ==============================================================================

    HardClipGUI.h
    Created: 6 Jan 2023 11:29:09am
    Author:  Raul

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "HardClipProcessor.h"
#include "GUIposition.h"
#include "CustomSliders.h"

/* This class has the components for the HardClip distortion */
class HardClipGUI : public Component,
                    public Slider::Listener
{
public:
    HardClipGUI();
    ~HardClipGUI();
    void sliderValueChanged(Slider* slider) override;
    void resized() override;
    void setHardClip(HardClipProcessor*);

    int sliderWidth = 150; //Make a function to set this size
    int sliderHeight = 150;
private:
    /**Reference to the HardClipProcessor class through a pointer to access and control HardClipProcessor class member functions*/
    HardClipProcessor* hardClipProcessPtr { nullptr };
    Slider clippingGainSldr;

    /*Object from a class which aim is place the different areas of the GUI to avoid repeat code*/
    GUIposition guiPosition;
    LookAndFeelDistortion lookAndFeelDistortion;
};