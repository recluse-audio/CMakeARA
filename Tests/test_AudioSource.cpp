#include <catch2/catch_test_macros.hpp>
#include "Timeline/Timeline_AudioSource.h"
#include "Util/Juce_Header.h"

TEST_CASE("AudioSource::getDurationInSamples()")
{
	juce::int64 sourceDurationInSamples = 100;
	juce::AudioBuffer<float> bufferSource(1, sourceDurationInSamples);
	Timeline::AudioSource source(bufferSource);
	CHECK(source.getDurationInSamples() == sourceDurationInSamples);
}
