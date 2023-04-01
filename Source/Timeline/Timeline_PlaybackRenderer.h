#pragma once
#include <Util/Juce_Header.h>

/**
	This class can hold one or many playback regions
	Given a process block this will look through its vector of playback regions to see if said process block will overlap with one of this renderers regions.
	If a region does overlap we use it to find what Audio Source it reads from, where to read from, and what modification to apply
*/
namespace Timeline
{


class PlaybackRenderer
{
public:
	PlaybackRenderer(){}
	~PlaybackRenderer(){}
	
private:
	
	
};

}
