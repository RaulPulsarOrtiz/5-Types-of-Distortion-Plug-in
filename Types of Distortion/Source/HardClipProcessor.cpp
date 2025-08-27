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
    if (input > 1)
    {
        return 1.f;
    }
    else if (input < -1)
    {
        return -1.f;
    }
    else
    {
        return input;
    }
}

void HardClipProcessor::setClippingGain(int newClippingGain)
{
    clippingGain = newClippingGain;
}

int HardClipProcessor::getClippingGain()
{
    return clippingGain.load();
}