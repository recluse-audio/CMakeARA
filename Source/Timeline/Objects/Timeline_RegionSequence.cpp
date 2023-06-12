#include "Timeline_RegionSequence.h"

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
