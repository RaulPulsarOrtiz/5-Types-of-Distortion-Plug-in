/*
  ==============================================================================

    AsymmetricalProcessor.h
    Created: 6 Jan 2023 2:42:01pm
    Author:  Raul

  ==============================================================================
*/

#pragma once
#include <atomic>

class AsymmetricalProcessor
{
public:
    AsymmetricalProcessor() {};
    ~AsymmetricalProcessor() {};

    /** Declaration of the process for an Asymmetrical Distortion.*/
    float asymmetrical(float input, float c);

    /**Sets the value to the asymmetric variable. This value comes from Editor Slider */
    void setAsymVariable(float newAsymVariableValue);
   
    /**@return the value that shape the asymmetrical distortion. (asymVariableValue) This variable is used in AudioProcessor for the Asymmetrical Type Distortion.
    This function is need to keep that variable private*/
    float getAsymVariable();

private:
    std::atomic<float> asymVariableValue = 1.f;

};