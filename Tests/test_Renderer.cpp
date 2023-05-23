#include <catch2/catch_test_macros.hpp>
#include "Util/Juce_Header.h"
#include "Timeline//Objects/Timeline_PlaybackRenderer.h"

// save some typing
using Int64Range = juce::Range<juce::int64>;

TEST_CASE("Find which region should be rendered")
{
	Timeline::PlaybackRenderer playbackRenderer;
	Int64Range blockRange(0, 10);
	juce::AudioBuffer<float> processBlock(1, 10);
	
	SECTION("No overlapping regions returns nullptr")
	{
		
	}
}
