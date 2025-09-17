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