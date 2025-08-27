/*
  ==============================================================================

    HardClipProcessor.h
    Created: 6 Jan 2023 11:57:45am
    Author:  Raul

  ==============================================================================
*/
#pragma once
#include <atomic>

class HardClipProcessor
{
public:
	HardClipProcessor() {};
	~HardClipProcessor() {};

	/** Declaration of the process for an HardClipping Distortion.*/
	float hardClipping(float input); 

	/**Sets the value to the clippingGain variable. This gain is needed in order to make the signal bigger and later clip it to the bounds. This value comes from Editor Slider */
	void setClippingGain(int newClippingGain);

	/**@return the clippingGain value. This variable is used in AudioProcessor for the HardClip Type Distortion.
		This function is need to keep that variable private */
	int getClippingGain();
	
private:
	std::atomic<float> clippingGain = 1.f; //This is already in dB
};
