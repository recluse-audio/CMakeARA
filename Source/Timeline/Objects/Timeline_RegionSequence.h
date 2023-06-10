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
	RegionSequence(){}
	~RegionSequence(){}
	
	virtual std::vector<Timeline::PlaybackRegion*> getPlaybackRegions() = 0;
private:
	
	
};

}
