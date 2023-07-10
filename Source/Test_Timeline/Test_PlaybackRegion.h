
#pragma once
#include "Util/Juce_Header.h"
#include "Timeline/Objects/Timeline_PlaybackRegion.h"
#include "Timeline/Objects/Timeline_AudioSource.h"
#include "Timeline/Objects/Timeline_AudioModification.h"

namespace Test
{
/**
	An easy to instantiate version of the Timeline::PlaybackRegion base class that I will use for testing purposes
*/
class PlaybackRegion : public Timeline::PlaybackRegion
{
public:
	PlaybackRegion(Timeline::AudioSource& audioSource, Timeline::AudioModification& audioMod)
	: Timeline::PlaybackRegion(audioSource, audioMod)
	{
		
	}
	

	// Not bothering to set SampleRate properly in Test class
	juce::Range<double> getRangeInTimelineSeconds() const override
	{
		double testSampleRate = 44100;
		double start = (double) mRangeInTimeline.getStart() / testSampleRate;
		double end = (double) mRangeInTimeline.getEnd() / testSampleRate;
		return juce::Range<double>(start, end);
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
