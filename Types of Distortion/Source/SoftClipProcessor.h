/*
  ==============================================================================

    SoftClipProcessor.h
    Created: 6 Jan 2023 12:55:22pm
    Author:  Raul

  ==============================================================================
*/

#pragma once
//#include <JuceHeader.h>
#include <cmath>
#include <atomic>

class SoftClipProcessor
{
public:
    SoftClipProcessor() {};
    ~SoftClipProcessor() {};

    /** Declaration of the process for an HardClipping Distortion.*/
    float softClipping(float input, int a); 

    /**Sets the value to the softCurve variable. This value comes from Editor Slider */
    void setSoftCurve(int newSoftCurve); // Set the SoftClip distortion curve value wanted

    /**@return the softCurve value. This variable is used in AudioProcessor for the softClip Type Distortion.
        This function is need to keep that variable private */
    int getSoftCurve();

private:
    //std::atomic<int> softClippingGain = 1;
    std::atomic<int> softCurveValue = 10;
};