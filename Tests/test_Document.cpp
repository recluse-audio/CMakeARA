#include <catch2/catch_test_macros.hpp>
#include <Util/Juce_Header.h>

#include "Timeline/Objects/Timeline_Document.h"
#include "Timeline/Objects/Timeline_RegionSequence.h"

#include "Test_Timeline/Test_RegionSequence.h"
#include "Test_Timeline/Test_PlaybackRegion.h"




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
	Timeline::RegionSequence sequence;
	size_t numRegions = 4;
	for(size_t i = 0; i < numRegions; i++)
	{
		auto newRegion = new Test::PlaybackRegion();
		sequence.addPlaybackRegion(newRegion);
	}

	auto regions = sequence.getPlaybackRegions();
	REQUIRE(regions.size() == numRegions);

}
