#include <catch2/catch_test_macros.hpp>
#include "TestTimeline/Test_AudioSource.h"
#include "Util/Juce_Header.h"

using Int64Range = juce::Range<juce::int64>;

TEST_CASE("Test the testing functions")
{
	auto source = std::make_unique<Test::AudioSource>();
	source->generateWithAllOnes(1, 100);
	auto buffer = source->getBuffer();
	CHECK(buffer->getNumSamples() == 100);
}
