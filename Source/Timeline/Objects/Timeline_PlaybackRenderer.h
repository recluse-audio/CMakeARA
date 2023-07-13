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
	PlaybackRenderer();
	~PlaybackRenderer();
	
	// Simply knowing the start in timeline samples would suffice if necessary to change
	void processBlock(juce::AudioBuffer<float>& block, Int64Range blockRangeInTimeline);

	void addPlaybackRegion(Timeline::PlaybackRegion* pRegion);
	int getNumRegions();
private:
	friend class RendererTester;
	std::vector<Timeline::PlaybackRegion*> mPlaybackRegions;

	// this could be passed a PlaybackRegion instead of an AudioSource if that helps
	void _readFromAudioSource(juce::AudioBuffer<float>& bufferToWriteTo,
							 Int64Range blockRangeInTimeline,
							 Timeline::PlaybackRegion* pRegion);
	
	void _applyAudioModification(juce::AudioBuffer<float>& bufferToModify,
								 Timeline::PlaybackRegion* pRegion);

	void _writeToProcessBlock(juce::AudioBuffer<float>& regionBlock, 
							  juce::AudioBuffer<float>& processBlock,
							  Int64Range rangeToWriteTo);
};

}
