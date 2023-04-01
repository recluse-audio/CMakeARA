
#pragma once
#include "Util/Juce_Header.h"

namespace Timeline
{

/**
	This class represents a vector of values that can be considered amplitude values of an audio source.
	In a practical sense, this "vector" would be a juce::File or ARAAudioSource that is read with a juce::AudioFormatReader or something of the sort
	Such a source would have its own
 
	This base
 */
class AudioSource
{

public:
	AudioSource(juce::AudioBuffer<float> bufferSource);
	~AudioSource();
	
	// Sub-classes will override this to ask their different type of source how many samples
	// This (kind of a base) class asks its buffer how many samples it has
	virtual juce::int64 getDurationInSamples() const;
	

	// TODO: Might need to getNumChannels()?
	
private:
	std::unique_ptr<juce::AudioBuffer<float>> mBufferSource;
	
};

}
