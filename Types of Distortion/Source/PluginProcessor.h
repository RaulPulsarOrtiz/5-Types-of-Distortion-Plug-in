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
    void setOutputGain(float newOutputGain);
    void setFilterFreqCutoff(int newFreq);
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

    enum TypeOfDistortion
    {
        Off,
        HardClipType,
        SoftClipType,
        QuarterCicleType,
        AsymmetricType
    };

    TypeOfDistortion typeOfDistortion;
    void setDistortionType(TypeOfDistortion newType);

    //Other types of fliters, useful for other cases:
    enum FilterType
    {
        LowPass,
        HighPass
    };

    FilterType filterType; // { FilterType::LowPass };
    void setFilterType (FilterType filterType);
private:

    std::atomic<float> outputGain = 1.f;
    std::atomic<int> wetAmount = 1;
    std::atomic<int> dryAmount = 0;
    float fDry = 0.f;
    float fWet = 0.f;


    std::atomic<int> freqCutoff = 20000;
    void reset() override;
    dsp::StateVariableTPTFilter<float> filter;

    HardClipProcessor hardClipProcessor;
    SoftClipProcessor softClipProcessor;
    QuarterCircleProcessor quarterCircleProcessor;
    AsymmetricalProcessor asymmetricalProcessor;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TypesofDistortionAudioProcessor)
};
