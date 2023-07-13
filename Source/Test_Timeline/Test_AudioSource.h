
#pragma once
#include "../Util/Juce_Header.h"
#include "../Timeline/Objects/Timeline_AudioSource.h"

namespace Test
{
/**
	An easy to instantiate version of the Timeline::AudioSource base class that I will use for testing purposes
 
 */
class AudioSource : public Timeline::AudioSource
{
public:
	using Int64Range = juce::Range<juce::int64>;
	
	AudioSource(const AudioSource&) = delete;
	AudioSource& operator=(const AudioSource&) = delete;
	AudioSource()
	{
		sourceBuffer = std::make_unique<juce::AudioBuffer<float>>(1, 100);
	}
	
	~AudioSource()
	{
		sourceBuffer.reset();
	}
	
	bool readFromAudioSource(juce::AudioBuffer<float>& bufferToWriteTo,
							 juce::Range<juce::int64> rangeToRead) override
	{
		return Timeline::AudioSource::readRange(bufferToWriteTo, *sourceBuffer.get(), rangeToRead);
	}
	

	
	//
	juce::int64 getDurationInSamples() const override
	{
		return sourceBuffer->getNumSamples();
	}
	
	

	
	void setAudioSourceBuffer(juce::AudioBuffer<float>* buffer)
	{
		sourceBuffer.reset(buffer);
	}
	
	juce::AudioBuffer<float>* getBuffer()
	{
		return sourceBuffer.get();
	}
	
	
	
	
	
	
	
	// Fills the buffer with all ones
	void generateWithAllOnes(int numChannels, int numSamples)
	{
		sourceBuffer->clear();
		sourceBuffer->setSize(numChannels, numSamples);
		
		auto writeBuff = sourceBuffer->getArrayOfWritePointers();
		for(int channel = 0; channel < numChannels; channel++)
		{
			for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
			{
				writeBuff[channel][sampleIndex] = 1.f;
			}
		}

	}
	
	static void generateWithAllOnes(juce::AudioBuffer<float>& bufferToFill)
	{
		bufferToFill.clear();
		auto numChannels = bufferToFill.getNumChannels();
		auto numSamples = bufferToFill.getNumSamples();
		
		auto writeBuff = bufferToFill.getArrayOfWritePointers();
		for(int channel = 0; channel < numChannels; channel++)
		{
			for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
			{
				writeBuff[channel][sampleIndex] = 1.f;
			}
		}

	}
	
	
	static void generateSine(juce::AudioBuffer<float>& bufferToFill)
	{
		bufferToFill.clear();
		auto numChannels = bufferToFill.getNumChannels();
		auto numSamples = bufferToFill.getNumSamples();
		
		auto writeBuff = bufferToFill.getArrayOfWritePointers();
		for(int channel = 0; channel < numChannels; channel++)
		{
			for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
			{
				auto sample = std::sin( (sampleIndex * juce::MathConstants<float>::twoPi) / numSamples );
				writeBuff[channel][sampleIndex] = sample;
			}
		}

	}
	
	// Generates a sine wave in a stereo buffer that has different phase in each channel
	static void generateStereoSineWithPhaseVariance(juce::AudioBuffer<float>& bufferToFill)
	{
		bufferToFill.clear();
		auto numChannels = bufferToFill.getNumChannels();
		auto numSamples = bufferToFill.getNumSamples();
		
		if(numChannels != 2)
			return;
		
		auto writeBuff = bufferToFill.getArrayOfWritePointers();

		for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
		{
			auto leftSample = std::sin( (sampleIndex * juce::MathConstants<float>::twoPi) / numSamples );
			auto rightSample = std::sin( (sampleIndex * juce::MathConstants<float>::twoPi * 2.f ) / numSamples );

			writeBuff[0][sampleIndex] = leftSample;
			writeBuff[1][sampleIndex] = rightSample;
		}

	}

	// Sample [0] will be value 0., sample [1] will be 1.f sample [3] will be 3.f etc.
	// use this to make sure you copied the right "amplitudes" sample values from the source
	void generateNumbered(int numChannels, int numSamples)
	{
		sourceBuffer->clear();
		sourceBuffer->setSize(numChannels, numSamples);
		
		auto writeBuff = sourceBuffer->getArrayOfWritePointers();
		for(int channel = 0; channel < numChannels; channel++)
		{
			for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
			{
				writeBuff[channel][sampleIndex] = (float)sampleIndex;
			}
		}

	}
	
	// All samples will be set to their channel number.  Left channel = 0.f, Right channel = 1.f
	void generateStereo(int numSamples)
	{
		sourceBuffer->clear();
		sourceBuffer->setSize(2, numSamples);
		
		auto writeBuff = sourceBuffer->getArrayOfWritePointers();
		for(int channel = 0; channel < 2; channel++)
		{
			for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
			{
				writeBuff[channel][sampleIndex] = (float)channel;
			}
		}

	}
	

	
	
	// All samples will be set to their channel number.  Left channel = 0.f, Right channel = 1.f
	void generateStereo(juce::AudioBuffer<float>& bufferToFill)
	{
		bufferToFill.clear();
		auto numSamples = bufferToFill.getNumSamples();
		
		auto writeBuff = sourceBuffer->getArrayOfWritePointers();
		
		for(int channel = 0; channel < 2; channel++)
		{
			for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
			{
				writeBuff[channel][sampleIndex] = (float)channel;
			}
		}

	}
	

	
	

private:
	std::unique_ptr<juce::AudioBuffer<float>> sourceBuffer;
	
	
};

}
