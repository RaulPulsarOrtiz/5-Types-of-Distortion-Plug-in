/*
  ==============================================================================

    SoftClipProcessor.cpp
    Created: 6 Jan 2023 12:55:22pm
    Author:  Raul

  ==============================================================================
*/

#include "SoftClipProcessor.h"
#include <cmath>

// This is a exponential/log-based soft clip.
// Asymptotes at ±a/(a-1). With a=5, that’s ±1.25. (You can normalize to ±1 by dividing by a/(a-1).)
//The curve is still smoothand odd - symmetric.
//But the slope at 0 depends on a.For finite a, slope > 1 → small inputs get amplified slightly.
//Example: with a = 5, slope ≈ 1.25 at 0.
// 
//float SoftClipProcessor::softClipping(float input, int a)
//{
//    float output = 0;
//    if (input > 0)
//    {
//        output = (a / (a - 1)) * (1 - pow(a, -input));
//    }
//    else
//    {
//        output = (a / (a - 1)) * (-1 + pow(a, input));
//    }
//    return output;
//}

//Hyperbolic tangent soft clip
//Symmetrical, smooth S-shaped curve.
//Asymptotes at ±1 / drive × tanh(∞) = ±1.
//Slope at 0 is exactly 1.0, no matter the drive value(this is why it’s popular).
//Drive only controls how fast it bends into saturation.

float SoftClipProcessor::softClipping(float input, int a)
{
    // Safety guard
    if (a <= 0.0f)
        return input;

    // Tanh soft clipping
    // - "drive" controls saturation strength
    // - Normalized by tanh(drive) so max = ±1
    float output = std::tanh(a * input) / std::tanh(a);

    return output;
}

//void SoftClipProcessor::setSoftClippingGain(int newClippingGain)
//{
//    softClippingGain = newClippingGain;
//}

void SoftClipProcessor::setSoftCurve(int newSoftCurve)
{
       softCurveValue = newSoftCurve;
}

int SoftClipProcessor::getSoftCurve()
{
    return softCurveValue.load();
}