#include <catch2/catch_test_macros.hpp>
#include "TestTimeline/Test_AudioSource.h"
#include "Util/Juce_Header.h"

using Int64Range = juce::Range<juce::int64>;

TEST_CASE("Test the testing tool functions")
{
	auto source = std::make_unique<Test_AudioSource>();
	source->generateWithAllOnes(1, 100);
	auto buffer = source->getBuffer();
	CHECK(buffer->getNumSamples() == 100);
}

TEST_CASE("Writes To incoming buffer")
{
	Test_AudioSource source;
	source.generateWithAllOnes(1, 100);
	CHECK(source.getDurationInSamples() == 100);
	
	// generating numbered sample values to check that correct amplitude was written
	source.generateNumbered(1, 50);
	CHECK(source.getDurationInSamples() == 50);
	
	juce::AudioBuffer<float> bufferToWriteTo;
	Int64Range rangeToRead(20, 40);
	
	bufferToWriteTo.clear();
	bufferToWriteTo.setSize(1, 20);
	
	source.readFromAudioSource(bufferToWriteTo, rangeToRead);
	
	CHECK(bufferToWriteTo.getSample(0, 0) == 20.f);
	CHECK(bufferToWriteTo.getSample(0, 10) == 30.f);
	
	SECTION("Reading Stereo, but writing mono should average values and not crash")
	{
		
		bufferToWriteTo.clear();
		bufferToWriteTo.setSize(1, 20);
		
		juce::AudioBuffer<float> bufferToReadFrom(1, 20);
		bufferToReadFrom.clear();
		
		Int64Range rangeToRead(0, 20);

		source.readFromAudioSource(bufferToWriteTo, rangeToRead);
		//CHECK(bufferToWriteTo.getRMSLevel(0, 0, bufferToWriteTo.getNumSamples()) == 0.5f);
	}
}


TEST_CASE("Testing reading with different channel layouts for source and output buffer")
{
	juce::AudioBuffer<float> bufferToWriteTo(1, 20);
	juce::AudioBuffer<float> bufferToReadFrom(1, 20);
	
	bufferToWriteTo.clear();
	bufferToReadFrom.clear();
	
	Int64Range readRange(0, 19);
	
	// make sure this static is working
	Test_AudioSource::generateWithAllOnes(bufferToReadFrom);
	CHECK(bufferToReadFrom.getNumSamples() == 20);
	CHECK(bufferToReadFrom.getRMSLevel(0, 0, 19) == 1.f);
	
	SECTION("Same channel layout")
	{
		bufferToWriteTo.clear();
		bufferToReadFrom.clear();
		
		bufferToWriteTo.setSize(2, 20);
		CHECK(bufferToWriteTo.getRMSLevel(0, 0, bufferToWriteTo.getNumSamples()) == 0.f);
		bufferToReadFrom.setSize(2, 20);
		Test_AudioSource::generateWithAllOnes(bufferToReadFrom);
		
		auto sameChannelNum = Timeline::AudioSource::readSameChannelNum(bufferToWriteTo, bufferToReadFrom, readRange);
		auto readMonoWriteStereo = Timeline::AudioSource::readMonoWriteStereo(bufferToWriteTo, bufferToReadFrom, readRange);
		auto readStereoWriteMono = Timeline::AudioSource::readStereoWriteMono(bufferToWriteTo, bufferToReadFrom, readRange);

		CHECK(sameChannelNum == true);
		CHECK(readMonoWriteStereo == false);
		CHECK(readStereoWriteMono == false);
		
		for(int channel = 0; channel < 2; channel++)
		{
			for(int sampleIndex = 0; sampleIndex < readRange.getLength(); sampleIndex++)
			{
				auto writeSample = bufferToWriteTo.getSample(channel, sampleIndex);
				auto readSample = bufferToReadFrom.getSample(channel, sampleIndex);
				
				CHECK(writeSample == readSample);
			}
		}

	}
	
	SECTION("Read Mono write stereo")
	{
		bufferToWriteTo.clear();
		bufferToReadFrom.clear();
		
		int numSamples = 5;
		
		readRange.setStart(0);
		readRange.setEnd(numSamples);
		
		// Starts as all zeroes, 2 channel
		bufferToWriteTo.setSize(2, numSamples);
		CHECK(bufferToWriteTo.getRMSLevel(0, 0, bufferToWriteTo.getNumSamples()) == 0.f);
		
		// Mono buffer, fill with ones
		bufferToReadFrom.setSize(1, numSamples);
		Test_AudioSource::generateWithAllOnes(bufferToReadFrom);
		
		// Test each read function to be sure they don't read when they aren't supposed to
		auto sameChannelNum = Timeline::AudioSource::readSameChannelNum(bufferToWriteTo, bufferToReadFrom, readRange);
		auto readMonoWriteStereo = Timeline::AudioSource::readMonoWriteStereo(bufferToWriteTo, bufferToReadFrom, readRange); // expect true
		auto readStereoWriteMono = Timeline::AudioSource::readStereoWriteMono(bufferToWriteTo, bufferToReadFrom, readRange);

		// Check read success bools, make sure we didn't try to read or write any garbage our out of range
		CHECK(sameChannelNum == false);
		CHECK(readMonoWriteStereo == true);
		CHECK(readStereoWriteMono == false);
		
		// Using sqrt of 0.5 for equal loudness panning mono to stereo
		auto halfPower = std::sqrt(0.5f);

		for(int channel = 0; channel < 2; channel++)
		{
			for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
			{
				auto writeSample = bufferToWriteTo.getSample(channel, sampleIndex);
				CHECK(writeSample == halfPower);
			}
		}

	}
	
	
	SECTION("Read stereo write mono")
	{
		bufferToWriteTo.clear();
		bufferToReadFrom.clear();
		
		int numSamples = 128;
		readRange.setEnd(numSamples);
		
		// Starts as all zeroes, 2 channel
		bufferToWriteTo.setSize(1, numSamples);
		CHECK(bufferToWriteTo.getRMSLevel(0, 0, bufferToWriteTo.getNumSamples()) == 0.f);
		
		// Mono buffer, fill with ones
		bufferToReadFrom.setSize(2, numSamples);
		Test_AudioSource::generateStereoSineWithPhaseVariance(bufferToReadFrom);
		//Test_AudioSource::generateWithAllOnes(bufferToReadFrom);
		
		// Test each read function to be sure they don't read when they aren't supposed to
		auto sameChannelNum = Timeline::AudioSource::readSameChannelNum(bufferToWriteTo, bufferToReadFrom, readRange);
		auto readMonoWriteStereo = Timeline::AudioSource::readMonoWriteStereo(bufferToWriteTo, bufferToReadFrom, readRange); // expect true
		auto readStereoWriteMono = Timeline::AudioSource::readStereoWriteMono(bufferToWriteTo, bufferToReadFrom, readRange);

		// Check read success bools, make sure we didn't try to read or write any garbage our out of range
		CHECK(sameChannelNum == false);
		CHECK(readMonoWriteStereo == false);
		CHECK(readStereoWriteMono == true);
		
		
		
		
		// Copy directly from  bufferToReadFrom and compare with  readStereoWriteMono
		juce::AudioBuffer<float> expectedMonoBuffer(1, numSamples);
		expectedMonoBuffer.clear();
		
		auto buffRead = bufferToReadFrom.getArrayOfReadPointers();
		auto buffWrite = expectedMonoBuffer.getArrayOfWritePointers();
		
		for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
		{
			// Increment with sampleIndex but offset by start position in AudioSource
			auto readIndex = readRange.getStart() + sampleIndex;
			auto leftSample = buffRead[0][readIndex] * std::sqrt(0.5f); // multiply by halfPower point
			auto rightSample = buffRead[1][readIndex] * std::sqrt(0.5f);
			auto readSample = (leftSample + rightSample) / 2.f;
			
			buffWrite[0][sampleIndex] += readSample;
		}
		
		
		
		
		// Check that the actual mono output buffer matches the expected buffer
		const float* expected = expectedMonoBuffer.getReadPointer(0);
		const float* actual = bufferToWriteTo.getReadPointer(0);
		const float errorTolerance = 0.0001f;
		
		// No channel loop, should be mono
		for(int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
		{
			REQUIRE(std::abs(actual[sampleIndex] - expected[sampleIndex]) < errorTolerance);
			//REQUIRE(std::abs(actual[sampleIndex] - 1.f) < errorTolerance);

		}
		
		
		

	}
}


TEST_CASE("Test generating sine wave")
{
	juce::AudioBuffer<float> sineWaveBuffer(1, 128);
	sineWaveBuffer.clear();
	
	Test_AudioSource::generateSine(sineWaveBuffer);
	auto sineWaveRMS = sineWaveBuffer.getRMSLevel(0, 0, 128);
	auto halfPower = std::sqrt(0.5f); // sine wave rms is equal to this
	auto errorTolerance = 0.0001f;
	REQUIRE(std::abs(sineWaveRMS - halfPower) < errorTolerance);
}
