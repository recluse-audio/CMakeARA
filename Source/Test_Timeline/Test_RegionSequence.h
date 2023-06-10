
#pragma once
#include "Util/Juce_Header.h"
#include "Timeline/Objects/Timeline_RegionSequence.h"
#include "Test_Timeline/Test_PlaybackRegion.h"


namespace Test
{

/**
	A simple RegionSequence class that is easy to manipulate and test
 */
class RegionSequence : public Timeline::RegionSequence
{

public:
	RegionSequence(){}
	~RegionSequence()
	{
		mPlaybackRegions.clear();
	}
	
	void addRegionAtRange(juce::int64 start, juce::int64 end)
	{
		jassert(start < end);
		auto region = std::make_unique<Test::PlaybackRegion>();
		region->setRangeInTimeline(start, end);
		addPlaybackRegion(region.get());
	}

	std::vector<Timeline::PlaybackRegion*> getPlaybackRegions() override
	{
		return mPlaybackRegions;
	}
	
	void addPlaybackRegion(Timeline::PlaybackRegion* region)
	{
		mPlaybackRegions.push_back(region);
	}
	
	std::vector<Timeline::PlaybackRegion*> mPlaybackRegions;
	
};

}