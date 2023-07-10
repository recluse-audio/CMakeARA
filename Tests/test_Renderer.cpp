#include <catch2/catch_test_macros.hpp>
#include "Util/Juce_Header.h"
#include "Timeline//Objects/Timeline_PlaybackRenderer.h"
#include "Test_Timeline/Test_AudioSource.h"
#include "Test_Utils/ObjectFactory.h"
#include "Test_Utils/TestUtils.h"

// save some typing
using Int64Range = juce::Range<juce::int64>;




TEST_CASE("Adding a PlaybackRegion")
{
	TestUtils::SetupAndTeardown setupAndTeardown;

	ObjectFactory objectFactory;
	auto region = objectFactory.getPlaybackRegion();
	Timeline::PlaybackRenderer renderer;

	renderer.addPlaybackRegion(&region);
	CHECK(renderer.getNumRegions() == 1);


}

TEST_CASE("Should render processBlock() correctly")
{
	Timeline::PlaybackRenderer playbackRenderer;
	Int64Range blockRangeInTimeline(100, 110);
	juce::AudioBuffer<float> block(1, blockRangeInTimeline.getLength());
	block.clear();

	SECTION("processBlock() with no regions writes nothing")
	{
		playbackRenderer.processBlock(block);
		for(int i = 0; i < block.getNumSamples(); i++)
		{
			CHECK(block.getSample(0, i) == 0.f);
		}
	}

	TestUtils::SetupAndTeardown setupAndTeardown;
	ObjectFactory objectFactory;
	auto region = objectFactory.getPlaybackRegion();
	Int64Range regionRangeInTimeline(105, 115);
	region.setRangeInTimeline(regionRangeInTimeline.getStart(), regionRangeInTimeline.getEnd());
	region.setRangeInAudioSource(0, regionRangeInTimeline.getLength());
	objectFactory.generateAudioSource(100);

	playbackRenderer.addPlaybackRegion(&region);

	SECTION("processBlock() catches overlap of single added region")
	{
		playbackRenderer.processBlock(block);

		int startInProcessBlock = regionRangeInTimeline.getStart() - blockRangeInTimeline.getStart();

		// Should be writing zeros because we haven't reached the region yet
		for(int i = 0; i < startInProcessBlock; i++)
			CHECK(block.getSample(0, i) == 0.f);

		for(int j = startInProcessBlock; j < block.getNumSamples(); j++)
			CHECK(block.getSample(0, j) == 1.f);
	}
	
}
