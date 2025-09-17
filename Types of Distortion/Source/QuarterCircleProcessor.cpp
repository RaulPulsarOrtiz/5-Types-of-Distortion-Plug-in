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
        output = sqrt(1 - pow((input - 1), 2));
    }
    else
    {
        output = (sqrt((1 - pow((input + 1), 2)))) * -1;
    }

    return output;
}
