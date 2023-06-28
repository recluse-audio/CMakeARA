#pragma once
#include <Util/Juce_Header.h>

/**
	This class represents a sequence of regions, aka a "track" or "track lane"
*/
namespace Timeline
{

class PlaybackRegion;

class RegionSequence
{
public:
	RegionSequence();
	~RegionSequence();

	void addPlaybackRegion(Timeline::PlaybackRegion* pRegion);
	std::vector<Timeline::PlaybackRegion*> getPlaybackRegions();
	
	// Returns the timeline sample position of the final region
	juce::int64 getEndOfFinalRegion();
	
private:
	std::vector<Timeline::PlaybackRegion*> mPlaybackRegions;
	
};

}
