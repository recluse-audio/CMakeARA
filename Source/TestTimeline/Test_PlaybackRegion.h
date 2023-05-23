
#pragma once
#include "Util/Juce_Header.h"
#include "Timeline/Timeline_PlaybackRegion.h"
#include "Timeline/Timeline_AudioSource.h"

namespace Test
{
/**
	An easy to instantiate version of the Timeline::PlaybackRegion base class that I will use for testing purposes
*/
class PlaybackRegion : public Timeline::PlaybackRegion
{
public:
	PlaybackRegion()
	{
		
	}
	
	juce::Range<juce::int64> getRangeInTimeline() const override
	{
		return mRangeInTimeline;
	}
	
	juce::Range<juce::int64> getRangeInAudioSource() const override
	{
		return mRangeInAudioSource;
	}
	
	
	void setRangeInTimeline(juce::int64 startSample, juce::int64 endSample)
	{
		mRangeInTimeline.setStart(startSample);
		mRangeInTimeline.setEnd(endSample);
	}
	
	void setRangeInAudioSource(juce::int64 startSample, juce::int64 endSample)
	{
		mRangeInAudioSource.setStart(startSample);
		mRangeInAudioSource.setEnd(endSample);
	}
	

	
	
private:
	juce::Range<juce::int64> mRangeInTimeline;
	juce::Range<juce::int64> mRangeInAudioSource;
};

}
