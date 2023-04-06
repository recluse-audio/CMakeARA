#pragma once
#include <Util/Juce_Header.h>
#include "Timeline_AudioSource.h"

/**
	This class represents the data behind a region of time within a region sequence (i.e. track / lane, etc.)
 
	It must know the associated AudioMod / AudioSource / RegionSequence
 
	PlaybackRenderer will have region will ask this "what is your source?" and "what should I read from?"
 
	Note:  You can give this invalid and negative values.  Problems from this are avoided becuase this class is really just time positions
	Any inquiries about an invalid range will simply return a range of 0;
	
*/


namespace Timeline
{


class PlaybackRegion
{
public:

	// See 'getRenderInfo'
	struct RenderRanges
	{
		juce::Range<juce::int64> blockRangeToRender;
		juce::Range<juce::int64> audioSourceRangeToRead;
	};
	
	explicit PlaybackRegion(Timeline::AudioSource& audioSource);
	~PlaybackRegion();
	
	
	virtual juce::Range<juce::int64> getRangeInTimeline() const = 0;
	
	virtual juce::Range<juce::int64> getRangeInAudioSource() const = 0;

	// RenderRanges contain two juce::Range<juce::int64> ranges.
	// These tell you what portion of a process block is within a playback region, and what chunk of an audio source should be read and then rendered
	PlaybackRegion::RenderRanges getRenderRanges(juce::Range<juce::int64> blockRange);
	
	/** Give a block range, this tells you which portion overlaps with a playback region */
	static juce::Range<juce::int64> calculateBlockRangeToRender(juce::Range<juce::int64> blockRange,
																juce::Range<juce::int64> regionRangeInTimeline);
	
	/**
	    This function takes the range of the start / end position of a process block
		and returns the range of an audio source should be read for this region given
		the timeline position of the process block
	*/
	static juce::Range<juce::int64> calculateRangeToReadInAudioSource(juce::Range<juce::int64> blockRangeInTimeline,
																juce::Range<juce::int64> regionRangeInTimeline,
																	  juce::Range<juce::int64> regionRangeInSource);
	
	/** Calculates the offset*/
	static juce::int64 calculateAudioSourceReadOffset(juce::int64 regionStartInTimeline,
													  juce::int64 regionStartInAudioSource);

private:
	juce::Range<juce::int64> mRangeInTimeline;
	juce::Range<juce::int64> mRangeInAudioSource;
	Timeline::AudioSource& mAudioSource;

	
	
};




}
