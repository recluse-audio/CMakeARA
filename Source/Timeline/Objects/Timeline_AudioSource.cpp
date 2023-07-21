
#include "Timeline_AudioSource.h"

using namespace Timeline;
using Int64Range = juce::Range<juce::int64>;

AudioSource::AudioSource()
{

}

AudioSource::~AudioSource()
{
	
}


bool AudioSource::readRange(juce::AudioBuffer<float>& bufferToWriteTo,
					  juce::AudioBuffer<float>& bufferToReadFrom,
					  juce::Range<juce::int64> rangeToRead )
{
	
	if(bufferToWriteTo.getNumChannels() == bufferToReadFrom.getNumChannels())
		return Timeline::AudioSource::readSameChannelNum(bufferToWriteTo, bufferToReadFrom, rangeToRead);
	else if(bufferToWriteTo.getNumChannels() < bufferToReadFrom.getNumChannels())
		return Timeline::AudioSource::readStereoWriteMono(bufferToWriteTo, bufferToReadFrom, rangeToRead);
	else if(bufferToWriteTo.getNumChannels() > bufferToReadFrom.getNumChannels())
		return Timeline::AudioSource::readMonoWriteStereo(bufferToWriteTo, bufferToReadFrom, rangeToRead);

	return false;
}

bool AudioSource::readSameChannelNum(juce::AudioBuffer<float>& bufferToWriteTo,
							   juce::AudioBuffer<float>& bufferToReadFrom,
							   juce::Range<juce::int64> readRange)
{
	if(bufferToWriteTo.getNumChannels() != bufferToReadFrom.getNumChannels())
		return false;
	
	auto buffRead = bufferToReadFrom.getArrayOfReadPointers();
	auto buffWrite = bufferToWriteTo.getArrayOfWritePointers();
	
	for(int channel = 0; channel < bufferToWriteTo.getNumChannels(); channel++)
	{
		for(int sampleIndex = 0; sampleIndex < readRange.getLength(); sampleIndex++)
		{
			// Increment with sampleIndex but offset by start position in AudioSource
			auto readIndex = readRange.getStart() + sampleIndex;
			
			auto readSample = buffRead[channel][readIndex];
			
			buffWrite[channel][sampleIndex] = readSample;
		}
	}
	
	return true;
}

bool AudioSource::readMonoWriteStereo(juce::AudioBuffer<float> &bufferToWriteTo, juce::AudioBuffer<float> &bufferToReadFrom, juce::Range<juce::int64> readRange)
{
	   if(bufferToWriteTo.getNumChannels() <= bufferToReadFrom.getNumChannels())
		   return false;
	   
	   auto buffRead = bufferToReadFrom.getArrayOfReadPointers();
	   auto buffWrite = bufferToWriteTo.getArrayOfWritePointers();
	   
		// Using sqrt of 0.5 for equal loudness panning mono to stereo
		auto halfPower = std::sqrt(0.5f);
	
	   for(int channel = 0; channel < bufferToWriteTo.getNumChannels(); channel++)
	   {
		   for(int sampleIndex = 0; sampleIndex < readRange.getLength(); sampleIndex++)
		   {
			   // Increment with sampleIndex but offset by start position in AudioSource
			   auto readIndex = readRange.getStart() + sampleIndex;
			   
			   auto readSample = buffRead[0][readIndex];
			   
			   buffWrite[channel][sampleIndex] = readSample * halfPower;
		   }
	   }
	   
	return true;
}

bool AudioSource::readStereoWriteMono(juce::AudioBuffer<float>& bufferToWriteTo,
							   juce::AudioBuffer<float>& bufferToReadFrom,
							   juce::Range<juce::int64> readRange)
{
	if(bufferToWriteTo.getNumChannels() >= bufferToReadFrom.getNumChannels())
		return false;
	
	auto buffRead = bufferToReadFrom.getArrayOfReadPointers();
	auto buffWrite = bufferToWriteTo.getArrayOfWritePointers();
	

	for(int sampleIndex = 0; sampleIndex < readRange.getLength(); sampleIndex++)
	{
		// Increment with sampleIndex but offset by start position in AudioSource
		auto readIndex = readRange.getStart() + sampleIndex;
		auto leftSample = buffRead[0][readIndex] * std::sqrt(0.5f); // multiply by halfPower point
		auto rightSample = buffRead[1][readIndex] * std::sqrt(0.5f);
		auto readSample = (leftSample + rightSample) / 2.f;
		
		buffWrite[0][sampleIndex] += readSample;
	}
	
	
	return true;
}


juce::Range<juce::int64> getValidRange(juce::Range<juce::int64> rangeToRead, juce::AudioBuffer<float>& bufferToReadFrom)
{
	auto sourceRange = juce::Range<juce::int64>(0, bufferToReadFrom.getNumSamples() - 1);
	auto validatedRange = sourceRange.getIntersectionWith(rangeToRead);
	return validatedRange;
}


