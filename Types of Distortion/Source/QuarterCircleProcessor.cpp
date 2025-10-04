/*
  ==============================================================================

    QuarterCircleProcessor.cpp
    Created: 6 Jan 2023 2:04:26pm
    Author:  Raul

  ==============================================================================
*/

#include "QuarterCircleProcessor.h"
#include <cmath>

float QuarterCircleProcessor::quarterCircle(float input)
{
    float output = 0;
    if (input > 0)
    {
        float val = 1 - pow((input - 1), 2);
        if (val < 0) val = 0;          // prevent NaN from floating-point rounding
        output = sqrt(val);
    }
    else
    {
        float val = 1 - pow((input + 1), 2);
        if (val < 0) val = 0;          // prevent NaN
        output = -sqrt(val);
    }

    return output;
}
