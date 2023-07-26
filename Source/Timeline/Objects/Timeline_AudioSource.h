
#include "../Util/Juce_Header.h"
#pragma once


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
	// save some typing
	using Int64Range = juce::Range<juce::int64>;
	AudioSource();
	virtual ~AudioSource();
	
	//
	virtual bool readFromAudioSource(juce::AudioBuffer<float>& buffer, juce::Range<juce::int64> rangeInAudioSourceToRead) = 0;
	// Sub-classes will override this to ask their different type of source how many samples
	// This (kind of a base) class asks its buffer how many samples it has
	virtual juce::int64 getDurationInSamples() const = 0;

	
	/** Fills the buffer, You can specify a range with a length that is shorter than the length of the buffer to partially fill it, but it won't attempt to write to sample indices that aren't there */
	static bool readRange(juce::AudioBuffer<float>& bufferToWriteTo,
						  juce::AudioBuffer<float>& bufferToReadFrom,
						  Int64Range rangeToRead );
	
	//
	static bool readSameChannelNum(juce::AudioBuffer<float>& bufferToWriteTo,
								   juce::AudioBuffer<float>& bufferToReadFrom,
								   Int64Range readRange);
	
	//
	static bool readMonoWriteStereo(juce::AudioBuffer<float>& bufferToWriteTo,
								    juce::AudioBuffer<float>& bufferToReadFrom,
									Int64Range readRange);
	
	//
	static bool readStereoWriteMono(juce::AudioBuffer<float>& bufferToWriteTo,
								    juce::AudioBuffer<float>& bufferToReadFrom,
									Int64Range readRange);
	
	// TODO: Might need to getNumChannels()?
	// Returns the range, but only the part that overlaps with an audio buffer
	static juce::Range<juce::int64> getValidRange(Int64Range rangeToRead,
										   juce::AudioBuffer<float>& bufferToReadFrom);

private:
	
};

}
