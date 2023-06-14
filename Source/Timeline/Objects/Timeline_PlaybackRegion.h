#pragma once
#include <Util/Juce_Header.h>
#include "Timeline_AudioSource.h"


// save some typing
using Int64Range = juce::Range<juce::int64>;

namespace Timeline
{

/**
	This class represents the data behind a region of time within a region sequence (i.e. track / lane, etc.)
	It must know the associated AudioMod / AudioSource / RegionSequence
	PlaybackRenderer will have region will ask this "what is your source?" and "where should I read from?"
 
	Note:  You can give this invalid and negative values.  Problems from this are avoided becuase this class is really just time positions
	Any inquiries about an invalid range will simply return a range of 0;
*/
class PlaybackRegion : public juce::DynamicObject
{
public:
	// See 'getRenderInfo'
	// All range lengths should be equal
	struct RenderRanges
	{
		Int64Range rangeInBlock;
		Int64Range rangeInTimeline;
		Int64Range rangeInAudioSource;
	};
	
	PlaybackRegion();	
	
	virtual juce::Range<juce::int64> getRangeInTimeline() const = 0;

	virtual juce::Range<juce::int64> getRangeInAudioSource() const = 0;

	/**
		RenderRanges contain three juce::Range<juce::int64> ranges.
		These tell you what portion of a process block is within a playback region, and what chunk of an audio source should be read and then rendered
	*/
	PlaybackRegion::RenderRanges getRenderRanges(juce::Range<juce::int64> blockRange);
	
	/** This function is for getting the position within the blockRange (not timeline) to write to  */
	static juce::Range<juce::int64> calculateRangeToRenderInBlock(Int64Range fullBlockRangeInTimeline, Int64Range rangeToRenderInTimeline);
	
	/** Give a block range, this tells you which portion overlaps with a playback region */
	static juce::Range<juce::int64> calculateRangeToRenderInTimeline(Int64Range blockRange,
																	 Int64Range regionRangeInTimeline);
	
	/**
	    This function takes the range of the start / end position of a process block
		and returns the range of an audio source should be read for this region given
		the timeline position of the process block
	*/
	static juce::Range<juce::int64> calculateRangeToReadInAudioSource(Int64Range blockRangeInTimeline, Int64Range regionRangeInTimeline, Int64Range regionRangeInSource);
	
	/** Calculates the offset*/
	static juce::int64 calculateAudioSourceReadOffset(juce::int64 regionStartInTimeline,
													  juce::int64 regionStartInAudioSource);

private:
	juce::Range<juce::int64> mRangeInTimeline;
	juce::Range<juce::int64> mRangeInAudioSource;

	
	
};




}
