/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "HardClipGUI.h"
#include "SoftClipGUI.h"
//QuarterCicle is empty at the moment
#include "AsymmetricalGUI.h"
#include "GUIposition.h"
#include "dBMeter.h"
#include "CustomSliders.h"

//==============================================================================
/**
*/


class TypesofDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                               public Slider::Listener,
                                               public ComboBox::Listener,
                                               public MouseListener
{
public:
    TypesofDistortionAudioProcessorEditor (TypesofDistortionAudioProcessor&);
    ~TypesofDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void mouseDoubleClick(const MouseEvent& event) override;
   
private:
    /*This reference is provided as a quick way for your editor to
    *access the processor object that created it.
    */
    TypesofDistortionAudioProcessor& audioProcessor;
    /** ComboBox to choose the Distortion Type and to choose the Filter Type with a Listener to these ComboBoxes
    * This ComboBox:
    * - 0: Hard Clip
    * - 1: Soft Clip
    * - 2: Asymmetrical
    * - 3: Quarter Circle
    * Filter Type:
    * Low Pass Filter
    * High Pass Filter
    */
    ComboBox distortionTypeMenu, filterTypeMenu;

    /**Objects of the classes for each distortion type GUI: */
    HardClipGUI hardClipGUI;
    SoftClipGUI softClipGUI;
    //QuarterCicle
    AsymmetricalGUI asymmetricalGUI;

    Slider outputGainSldr, cutoffSldr, dryWetSldr;
    Label outputGainText, cutoffText, dryWetText, driveText, curveSoftClipText, curveAsymmetricText;

    GUIposition guiPosition;
    VerticalMeter inputMeterL, inputMeterR, outputMeterL, outputMeterR;
    
    LookAndFeel22Steps twentyTwoStepsLookAndFeel;
    MenuLookAndFeel menuLookAndFeel;
    InvertedMenuLookAndFeel invertedMenuLookAndFeel;
    Image wavesBackground;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TypesofDistortionAudioProcessorEditor)
};
