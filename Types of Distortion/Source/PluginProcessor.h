/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "HardClipProcessor.h"
#include "SoftClipProcessor.h"
#include "QuarterCircleProcessor.h"
#include "AsymmetricalProcessor.h"
#include <atomic>

//==============================================================================
/**
*/
class TypesofDistortionAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TypesofDistortionAudioProcessor();
    ~TypesofDistortionAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    /**Sets the value to the ouputGain variable. This value comes from Editor Slider */
    void setOutputGain(float newOutputGain);
    /**Sets the value of the filter cutoff frequency variable. This value comes from Editor Slider */
    void setFilterFreqCutoff(int newFreq);
    /**Sets the amount of Wet signal and do the invert to know the amout of Dry signal. This value comes from Editor Slider and use just one slider*/
    void setDryWetAmount(int newAmount);
    //==============================================================================

     /** @return HardClipProcessor*/
    HardClipProcessor* getHardClip() { return &hardClipProcessor; }

    /** @return SoftClipProcessor */
    SoftClipProcessor* getSoftClip() { return &softClipProcessor; }

    /** @return AsymmetricalProcessor */
    QuarterCircleProcessor* getQuarterCicle() { return &quarterCircleProcessor; }
    /** @return AsymmetricalProcessor */
    AsymmetricalProcessor* getAsymmetrical() { return &asymmetricalProcessor; }

    /**  enum to order the 5 types of Distortion available*/
    enum TypeOfDistortion
    {
        Off,
        HardClipType,
        SoftClipType,
        QuarterCicleType,
        AsymmetricType
    };

    /**  this variable can be set on 5 different types of Distortion. It's set on the Editor comboBox*/
    TypeOfDistortion typeOfDistortion;

    /**  Function to set a new type of Distortion to the typeOfDistortion variable from the enum TypeOfDistortion*/
    void setDistortionType(TypeOfDistortion newType);

    /**Function to set a new type of Filter to the filterType variable from the enum FilterType*/
    void setFilterType (juce::dsp::StateVariableTPTFilterType newType);
   
    /** This function returns the Input Signal and turn it from gain to decibels. 
    * This value is used by the @ref PluginEditor to initialise the
    * @ref VerticalMeter objects for PluginEditor::inputMeterL and PluginEditor::inputMeterR, allowing the meter to display live levels in the Editor from the processor.*/
    float getInputSignal(int channel);
    /** This function returns the Output Signal which is already in decibels.
    * This value is used by the @ref PluginEditor to initialise the
    * @ref VerticalMeter objects for PluginEditor::outputMeterL and PluginEditor::onputMeterR, allowing the meter to display live levels in the Editor from the processor.*/
    float getOutputSignal(int channel);

private:

    /** Increasing Drive can increase the overall signal output. This variable stores the Output Gain that can be used to bring down the signal to the same level as was in the input, or adjust it in other ways */
    std::atomic<float> outputGain = 1.f;
    /** Selects how much distorted signal we want in a range from 0 to 1. Altough the slider is expressed from 0 to 100 */
    std::atomic<float> wetAmount = 1.f;
    /** Selects how much dry signal we want in a range from 0 to 1. Altough the slider is expressed from 0 to 100 */
    std::atomic<float> dryAmount = 0.f;
    /** Stores the input signal without distortion */
    float fDry = 0.f;
    /** Stores the distorted signal */
    float fWet = 0.f;
    /** Stores the Filter's Frequency Cutoff*/
    std::atomic<int> freqCutoff = 20000;
    /** This function resets the filter state and the smoothValue used for the Auto-Gain feature. It is called at the end of prepareToPlay() */
    void reset() override;
    /** Declaration of the Filter. One for each leg of the stereo. */
    dsp::StateVariableTPTFilter<float> filterL, filterR;
    /** Stores the input and output signal levels in dB to be displayed on the @ref PluginEditor::inputMeterL, 
     * @ref PluginEditor::inputMeterR, @ref PluginEditor::outputMeterL, 
     * and @ref PluginEditor::outputMeterR*/
    float inputSignalL{ -60.f }, inputSignalR{ -60.f }, outputSignalL{ -60.f }, outputSignalR{ -60.f };

    juce::SmoothedValue<float> autoGainL{ 1.0f };
    juce::SmoothedValue<float> autoGainR{ 1.0f };
    float correctionL{ 1.0f }; //They need to be global here because the value result of that formula need to be remembered from the previous block to the next block. If they would be local they are deleted when the new block starts
    float correctionR{ 1.0f };
    float prevDistortedRMSOutputL{ 1.0f };
    float prevDistortedRMSOutputR{ 1.0f };

    /**Objects of the classes for each distortion type process: */
    HardClipProcessor hardClipProcessor;
    SoftClipProcessor softClipProcessor;
    QuarterCircleProcessor quarterCircleProcessor;
    AsymmetricalProcessor asymmetricalProcessor;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TypesofDistortionAudioProcessor)
};
