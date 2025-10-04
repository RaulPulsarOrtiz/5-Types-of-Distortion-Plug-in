/*
  ==============================================================================

    HardClipProcessor.cpp
    Created: 6 Jan 2023 11:57:45am
    Author:  Raul

  ==============================================================================
*/

#include "HardClipProcessor.h"

float HardClipProcessor::hardClipping(float input)
{
    float output = 0;
    if (input > 0.7f)
    {
        output = 0.7f;
    }
    else if (input < -0.7f)
    {
        output = -0.7f;
    }
    else
    {
        output = input;
    }
    return output;
}

void HardClipProcessor::setClippingGain(int newClippingGain)
{
    clippingGain = newClippingGain;
}

int HardClipProcessor::getClippingGain()
{
    return clippingGain.load();
}