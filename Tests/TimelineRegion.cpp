#include <catch2/catch_test_macros.hpp>
#include "MultiTrackTimeline/TimelineRegion.h"



TEST_CASE("Test Timeline Region Initialization Success")
{
	auto range = new juce::Range<double>(2.0, 4.0);
	
	auto region = new TimelineRegion(*range);
	CHECK(region->getStartTime() == 2.0);
	CHECK(region->getDuration() == 2.0);
	
}

TEST_CASE("Expect failure when constructed with invalid region data" )
{
//	auto obj = new juce::DynamicObject();
//	obj->setProperty("Start Time", 2.0);
//	obj->setProperty("Duration", -4.0);
//	auto regionInfo = juce::var::fromValue(obj);
//
//	auto region = new TimelineRegion(obj);
//	CHECK(region->getStartTime() == 2.0);
//	CHECK(region->getDuration == 4.0);
}
