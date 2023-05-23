
#include <catch2/catch_test_macros.hpp>
#include "Util/Juce_Header.h"
#include "Timeline/Timeline_PlaybackRegion.h"
#include "TestTimeline/Test_PlaybackRegion.h"
#include "TestTimeline/Test_AudioSource.h"

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
		auto rangeToRead = Timeline::PlaybackRegion::calculateRangeToRenderInTimeline(blockRange, rangeInTimeline);
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

TEST_CASE("Retrieving Render Ranges using Test::PlaybackRegion to simulate ARA ranges")
{
	Test::PlaybackRegion playbackRegion;
	
	SECTION("Test the test class set/get")
	{
		playbackRegion.setRangeInTimeline(100, 200);
		CHECK(playbackRegion.getRangeInTimeline().getStart()==100);
		CHECK(playbackRegion.getRangeInTimeline().getEnd()==200);

		playbackRegion.setRangeInAudioSource(0, 50);
		CHECK(playbackRegion.getRangeInAudioSource().getStart()==0);
		CHECK(playbackRegion.getRangeInAudioSource().getEnd()==50);
	}
	
}



TEST_CASE("Should write to correct part of blockRange when only writing to a portion of block")
{
	SECTION("Should handle blocks that only partially overlap")
	{
		auto fullBlockRangeInTimeline = Int64Range(5, 10);
		auto rangeToRenderInTimeline = Int64Range(8, 10);
		auto rangeToRenderInBlock = Timeline::PlaybackRegion::calculateRangeToRenderInBlock(fullBlockRangeInTimeline, rangeToRenderInTimeline);

		CHECK(rangeToRenderInBlock.getStart() == 3);
		CHECK(rangeToRenderInBlock.getEnd() == 5);
	}


}


TEST_CASE("Simulating how the PlaybackRenderer will get the correct render range")
{
	Test::PlaybackRegion playbackRegion;
	playbackRegion.setRangeInTimeline(2, 7);
	playbackRegion.setRangeInAudioSource(1, 6);
	
	// The range of the block in the timeline NOT the block itself.  I.e. doesn't always start at 0
	Int64Range blockRangeInTimeline;
	blockRangeInTimeline.setStart(1);
	blockRangeInTimeline.setEnd(3);
	
	auto renderRanges = playbackRegion.getRenderRanges(blockRangeInTimeline);
	auto rangeInTimeline = renderRanges.rangeInTimeline;
	auto rangeInAudioSource = renderRanges.rangeInAudioSource;
	
	//CHECK(rangeInBlock.getStart() == 2);
}
