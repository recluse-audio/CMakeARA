#include "Timeline_RegionSequence.h"
#include "Timeline_PlaybackRegion.h"

using namespace Timeline;

RegionSequence::RegionSequence()
{
	
}

RegionSequence::~RegionSequence()
{
	
}

void RegionSequence::addPlaybackRegion(Timeline::PlaybackRegion *pRegion)
{
	mPlaybackRegions.push_back(pRegion);
}

std::vector<Timeline::PlaybackRegion*> RegionSequence::getPlaybackRegions()
{
	return mPlaybackRegions;
}


juce::int64 RegionSequence::getEndOfFinalRegion()
{
	juce::int64 endSample = 0;
	for (auto region : mPlaybackRegions)
	{
		auto lastSampleInRegion = region->getRangeInTimeline().getEnd();
		if(lastSampleInRegion > endSample)
			endSample = lastSampleInRegion;
	}
	return endSample;
}
