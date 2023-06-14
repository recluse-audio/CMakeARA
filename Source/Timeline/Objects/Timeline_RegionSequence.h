#pragma once
#include <Util/Juce_Header.h>

/**
	This class represents a sequence of regions, aka a "track" or "track lane"
*/
namespace Timeline
{

class PlaybackRegion;

class RegionSequence : public juce::DynamicObject
{
public:
	RegionSequence();
	~RegionSequence();

	void addPlaybackRegion(Timeline::PlaybackRegion* pRegion);
	std::vector<Timeline::PlaybackRegion*> const& getPlaybackRegions();
	
private:
	std::vector<Timeline::PlaybackRegion*> mPlaybackRegions;
	
};

}
