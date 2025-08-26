/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TypesofDistortionAudioProcessor::TypesofDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

TypesofDistortionAudioProcessor::~TypesofDistortionAudioProcessor()
{
}

//==============================================================================
const juce::String TypesofDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TypesofDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TypesofDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TypesofDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TypesofDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TypesofDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TypesofDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TypesofDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TypesofDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void TypesofDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TypesofDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();

    filter.prepare(spec);
    reset();
}

void TypesofDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TypesofDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TypesofDistortionAudioProcessor::setDistortionType(TypeOfDistortion newType)
{
    typeOfDistortion = newType;
}

float TypesofDistortionAudioProcessor::getInputSignal(int channel)
{
    if (channel == 0)
    {
        return inputSignalL; 
    }
    else if (channel == 1)
    {
        return inputSignalR;
    }
}

float TypesofDistortionAudioProcessor::getOutputSignal(int channel)
{
    if (channel == 0)
    {
        return outputSignalL;
    }
    else if (channel == 1)
    {
        return outputSignalR;
    }
}

void TypesofDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    float fMix = 0;
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    filter.setCutoffFrequency(freqCutoff);
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
   
    inputSignalL = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    inputSignalR = buffer.getRMSLevel(1, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        // ..do something to the data...
        

        if (typeOfDistortion == Off)
        {
           // for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
           // {
           //     channelData[sample] = buffer.getSample(channel, sample);
           //     fMix = channelData[sample];
           //     channelData[sample] = fMix;
           // channelData[sample] *= outputGain;
           // }
            outputSignalL = inputSignalL;
            outputSignalR = inputSignalR;
        }

        if (typeOfDistortion == HardClipType)
        {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = buffer.getSample(channel, sample);
                fDry = channelData[sample];
                
                fMix = channelData[sample] * hardClipProcessor.getClippingGain();
                float fClipped = hardClipProcessor.hardClipping(fMix);
                               
                float fFiltered = filter.processSample(channel, fClipped);
                fWet = fFiltered;
                channelData[sample] = (fWet * wetAmount.load()) + (fDry * dryAmount.load());
                
                channelData[sample] *= outputGain.load();
            }
        }
        
        else if (typeOfDistortion == SoftClipType)
        {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = buffer.getSample(channel, sample);
                fDry = channelData[sample];
                fMix = channelData[sample] * (hardClipProcessor.getClippingGain() * 0.17); //Reduce the range of scale from 1 - 30 to 1 - 5.1

                float hardClipped = hardClipProcessor.hardClipping(fMix);
           
                channelData[sample] = softClipProcessor.softClipping(hardClipped, softClipProcessor.getSoftCurve());
                float fFiltered = filter.processSample(channel, channelData[sample]);
                fWet = fFiltered;
                channelData[sample] = (fWet * wetAmount.load()) + (fDry * dryAmount.load());
                channelData[sample] *= outputGain.load();
            }
        }

        else if (typeOfDistortion == QuarterCicleType)
        {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = buffer.getSample(channel, sample);
                fDry = channelData[sample];
                fMix = channelData[sample] * hardClipProcessor.getClippingGain() * 0.17; //Reduce the range of scale from 1 - 30 to 1 - 5.1

                float hardClipped = hardClipProcessor.hardClipping(fMix);
                hardClipped *= 0.4;

                channelData[sample] = quarterCircleProcessor.quarterCircle(hardClipped);
                float fFiltered = filter.processSample(channel, channelData[sample]);
                fWet = fFiltered;
                channelData[sample] = (fWet * wetAmount.load()) + (fDry * dryAmount.load());
                channelData[sample] *= outputGain.load();
            }
        }

        else if (typeOfDistortion == AsymmetricType)
        {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = buffer.getSample(channel, sample);
                fDry = channelData[sample];
                fMix = channelData[sample] * hardClipProcessor.getClippingGain() * 0.17; //Reduce the range of scale from 1 - 30 to 1 - 5.1

                float hardClipped = hardClipProcessor.hardClipping(fMix);
                hardClipped *= 0.4;

                channelData[sample] = asymmetricalProcessor.asymmetrical(hardClipped, asymmetricalProcessor.getAsymVariable());
                float fFiltered = filter.processSample(channel, channelData[sample]);
                fWet = fFiltered;
                channelData[sample] = (fWet * wetAmount.load()) + (fDry * dryAmount.load());
                channelData[sample] *= outputGain.load();
                
            }
        }

        if (channel == 0)
            outputSignalL = buffer.getRMSLevel(channel, 0, buffer.getNumSamples());
        else if (channel == 1)
            outputSignalR = buffer.getRMSLevel(channel, 0, buffer.getNumSamples());
    }

}

//==============================================================================
bool TypesofDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TypesofDistortionAudioProcessor::createEditor()
{
    return new TypesofDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void TypesofDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TypesofDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
void TypesofDistortionAudioProcessor::setOutputGain(float newOutputGain)
{
    outputGain = newOutputGain;
}

void TypesofDistortionAudioProcessor::setFilterFreqCutoff(int newFreq)
{
    freqCutoff = newFreq;
}

void TypesofDistortionAudioProcessor::setDryWetAmount(int newAmount)
{
    wetAmount = newAmount;
    dryAmount = 1 - newAmount;
}

//==============================================================================
void TypesofDistortionAudioProcessor::setFilterType(FilterType newFilterType)
{
    filterType = newFilterType;

    if (filterType == LowPass)
    {
        filter.setType(dsp::StateVariableTPTFilterType::lowpass);
    }

    else if (filterType == HighPass)
    {
        filter.setType(dsp::StateVariableTPTFilterType::highpass);
    }
}
   // switch (filterType)
   // {
   // case FilterType::LowPass:
   //     {
   //     filter.setType(dsp::StateVariableTPTFilterType::lowpass);
   //     break;
   //     }
   // case FilterType::BandPass:
   //     {
   //     filter.setType(dsp::StateVariableTPTFilterType::bandpass);
   //     break;
   //     }
   // case FilterType::HighPass:
   //     {
   //     filter.setType(dsp::StateVariableTPTFilterType::highpass);
   //     break;
   //     }
   // }


//==============================================================================
void TypesofDistortionAudioProcessor::reset()
{
    filter.reset();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TypesofDistortionAudioProcessor();
}
