#pragma once
#include "Util/Juce_Header.h"
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

	// Position info of the playback region in samples
	struct PositionInfo
	{
		juce::int64 startInTimeline = 0;
		juce::int64 startInAudioSource = 0;
		juce::int64 duration;
	};
	
	explicit PlaybackRegion(PlaybackRegion::PositionInfo posInfo,
							Timeline::AudioSource& audioSource);
	~PlaybackRegion();
	
	
	virtual juce::Range<juce::int64> getRangeInTimeline() const;
	
	juce::Range<juce::int64> getRangeInAudioSource() const;

	
	/**
	    This function takes the range of the start / end position of a process block
		and returns the range of an audio source should be read for this region given
		the timeline position of the process block
	*/
	juce::Range<juce::int64> getRangeToReadInAudioSource(juce::Range<juce::int64> blockRange);
	

	
private:
	juce::Range<juce::int64> mRangeInTimeline;
	juce::Range<juce::int64> mRangeInAudioSource;
	Timeline::AudioSource& mAudioSource;

	
	
};




}
