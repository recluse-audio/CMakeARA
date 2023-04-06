
#include <catch2/catch_test_macros.hpp>
#include "Util/Juce_Header.h"
#include "Timeline/Timeline_PlaybackRegion.h"

// save some typing
using Int64Range = juce::Range<juce::int64>;

//class PlaybackRegionTester
//{
//public:
//	PlaybackRegionTester(Timeline::PlaybackRegion& region) : mRegion(region)
//	{
//
//	}
//	void calculateBlockRangeToRender(Int64Range blockRange, Int64Range regionRangeInTimeline, Int64Range)
//}


TEST_CASE("Calculating range to read in audio source")
{
	auto rangeInTimeline = Int64Range(4,7);
	auto rangeInAudioSource = Int64Range(2,5);
	
	auto readOffset = Timeline::PlaybackRegion::calculateAudioSourceReadOffset(rangeInTimeline.getStart(), rangeInAudioSource.getStart());
	CHECK(readOffset == -2);
	
	SECTION("Block not overlapping playback region nor audio source should return range 0")
	{
		auto blockRange = Int64Range(0,1);
		auto rangeToRead = Timeline::PlaybackRegion::calculateBlockRangeToRender(blockRange, rangeInTimeline);
		CHECK(rangeToRead.isEmpty() == true);

	}

	SECTION("Block with entire duration within playback regions duration")
	{
		auto blockRange = Int64Range(5,6);
		auto rangeToRead = Timeline::PlaybackRegion::calculateRangeToReadInAudioSource(blockRange, rangeInTimeline, rangeInAudioSource);
		CHECK(rangeToRead.getStart() == 3);
		CHECK(rangeToRead.getEnd() == 4);

	}
	
	SECTION("Block with partial duration within playback regions duration")
	{
		auto blockRange = Int64Range(6,8);
		auto rangeToRead = Timeline::PlaybackRegion::calculateRangeToReadInAudioSource(blockRange, rangeInTimeline, rangeInAudioSource);
		CHECK(rangeToRead.getStart() == 4);
		CHECK(rangeToRead.getEnd() == 5);

	}
}
