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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TypesofDistortionAudioProcessor& audioProcessor;
    
    ComboBox distortionTypeMenu, filterTypeMenu;

    /**Objects of the classes for each distortion type GUI: */
    HardClipGUI hardClipGUI;
    SoftClipGUI softClipGUI;
    //QuarterCicle
    AsymmetricalGUI asymmetricalGUI;

    Slider outputGainSldr, cutoffSldr, dryWetSldr;
    Label outputGainText, cutoffText, dryWetText;

    juce::Rectangle<int> getWorkingArea();
    juce::Rectangle<int> getAnalyserArea();
    juce::Rectangle<int> getKnobsArea();
    GUIposition guiPosition;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TypesofDistortionAudioProcessorEditor)
};
