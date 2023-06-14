#include <catch2/catch_test_macros.hpp>
#include <Util/Juce_Header.h>

#include "Timeline/Objects/Timeline_Document.h"
#include "Timeline/Objects/Timeline_RegionSequence.h"

#include "Test_Timeline/Test_RegionSequence.h"
#include "Test_Timeline/Test_PlaybackRegion.h"




TEST_CASE("Add RegionSequence to document")
{
	Timeline::Document document;
	const size_t numSequences = 2;
	for(size_t i = 0; i < numSequences; i++)
	{
		document.addRegionSequence(new Timeline::RegionSequence());
	}
	const auto& regionSequences = document.getRegionSequences();
	REQUIRE(regionSequences.size()==numSequences);
}



