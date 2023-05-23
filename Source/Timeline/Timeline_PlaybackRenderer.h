#pragma once
#include <Util/Juce_Header.h>


// save some typing
using Int64Range = juce::Range<juce::int64>;

namespace Timeline
{

class PlaybackRegion;





//===========================================
/**
	This class can hold one or many playback regions
	Given a process block this will look through its vector of playback regions to see if said process block will overlap with one of this renderers regions.
	If a region does overlap we use it to find what Audio Source it reads from, where to read from, and what modification to apply
 
 NOTE: Don't try and test if it can return its vector of playback regions, we should be able to trust ARA / the hosts for that and can't do anything about it if they are fucking up
 Test that it can identify whi
*/
//===========================================
class PlaybackRenderer
{
public:
	PlaybackRenderer(){}
	~PlaybackRenderer(){}
	
	/** Instructions on what to read and from which playbackRegion and where to write in the processBlock*/
	struct ReadInstructions
	{
		std::unique_ptr<Timeline::PlaybackRegion> playbackRegion;
		Int64Range readRangeInPlaybackRegion;
		Int64Range writeRangeInProcessBlock;
	};
	
	
	/**
		Given a blockRange, this returns a vector of ReadInstructions,
		a simple data container that tells you what to read from a region.
		Returns an empty vector if no regions overlapped with blockRange
	*/
	static std::vector<ReadInstructions> collectReadInstructions( Int64Range blockRange,
																  std::vector<Timeline::PlaybackRegion> regions );
	
	
	
private:

	
};

}
