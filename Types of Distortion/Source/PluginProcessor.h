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

    /** enum with two types of filters*/
    //enum FilterType
    //{
    //    LowPass,
    //    HighPass
    //};

    /**  this variable can be set on 2 different types of Filters. It's set on the Editor comboBox*/
  //  FilterType filterType;

    /**Function to set a new type of Filter to the filterType variable from the enum FilterType*/
    void setFilterType (juce::dsp::StateVariableTPTFilterType newType);
   
    float getInputSignal(int channel);
    float getOutputSignal(int channel);

private:

    std::atomic<float> outputGain = 1.f;
    std::atomic<int> wetAmount = 1;
    std::atomic<int> dryAmount = 0;
    float fDry = 0.f;
    float fWet = 0.f;


    std::atomic<int> freqCutoff = 20000;
    void reset() override;
    dsp::StateVariableTPTFilter<float> filterL, filterR;

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
