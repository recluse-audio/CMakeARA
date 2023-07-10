#include <catch2/catch_test_macros.hpp>
#include <Util/Juce_Header.h>

#include "Timeline/Objects/Timeline_Document.h"
#include "Timeline/Objects/Timeline_RegionSequence.h"

#include "Test_Timeline/Test_RegionSequence.h"
#include "Test_Timeline/Test_PlaybackRegion.h"
#include "Test_Timeline/Test_AudioSource.h"

#include "Test_Utils/TestUtils.h"





TEST_CASE("Add sub-class of RegionSequence to Document")
{
	Timeline::Document document;
	size_t numSequences = 4;
	for(size_t i = 0; i < numSequences; i++)
	{
		auto newSequence = new Test::RegionSequence();
		document.addRegionSequence(newSequence);
	}

	auto sequences = document.getRegionSequences();
	REQUIRE(sequences.size() == numSequences);

}


TEST_CASE("Add sub-class of PlaybackRegion to RegionSequence")
{
	TestUtils::SetupAndTeardown setupAndTeardown;

	Test::AudioSource audioSource;
	juce::UndoManager undoManager;
	Timeline::AudioModification audioMod(undoManager);
	Timeline::RegionSequence sequence;
	size_t numRegions = 4;
	for(size_t i = 0; i < numRegions; i++)
	{
		auto newRegion = new Test::PlaybackRegion(audioSource, audioMod);
		sequence.addPlaybackRegion(newRegion);
	}

	auto regions = sequence.getPlaybackRegions();
	REQUIRE(regions.size() == numRegions);
}


TEST_CASE("Can return the timeline length accurately")
{
	Timeline::Document document;

	SECTION("Should always be at least 120 seconds in length no matter what")
	{
		CHECK(document.getTimelineLength() >= document.minTimelineLength);
	}

}