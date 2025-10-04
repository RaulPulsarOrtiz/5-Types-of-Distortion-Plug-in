/*
  ==============================================================================

    AsymmetricalProcessor.cpp
    Created: 6 Jan 2023 2:42:01pm
    Author:  Raul

  ==============================================================================
*/

#include "AsymmetricalProcessor.h"
#include <cmath>

float AsymmetricalProcessor::asymmetrical(float input, float c)
{
    float epsilon = 1e-6f;
    if (fabs(input) < epsilon)
        return input;  // bypass tiny values to avoid noise

    float a = 1 / (c + 1);
    float output = 0;

    if (input > 0)
    {
        output = input;
    }
    else
    {
        output = input + (pow(input * -1, a) / a);
    }
    // Add a minimum factor so very small negative inputs don’t cancel
    if (c == 0.0f && input < 0.0f)
        output = input * 0.2f;  // small but nonzero output

    return output;
}

void AsymmetricalProcessor::setAsymVariable(float newAsymVariableValue)
{
    asymVariableValue = newAsymVariableValue;
}

float AsymmetricalProcessor::getAsymVariable()
{
    return asymVariableValue.load();
}