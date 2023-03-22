
#include "Timeline_PlaybackRegion.h"
#include "Timeline_AudioSource.h"

using namespace Timeline;

PlaybackRegion::PlaybackRegion(PlaybackRegion::PositionInfo posInfo,
							   Timeline::AudioSource& audioSource)
: mAudioSource(audioSource)
{
	mRangeInTimeline.setStart(posInfo.startInTimeline);
	mRangeInTimeline.setEnd(posInfo.startInTimeline + posInfo.duration);
	
	mRangeInAudioSource.setStart(posInfo.startInAudioSource);
	
	juce::int64 endInSource = posInfo.startInAudioSource + posInfo.duration;
	
	if(endInSource > audioSource.getDurationInSamples())
		endInSource = audioSource.getDurationInSamples();
		
}

PlaybackRegion::~PlaybackRegion()
{
	
}

juce::Range<juce::int64> PlaybackRegion::getRangeInTimeline() const
{
	return mRangeInTimeline;
}

juce::Range<juce::int64> PlaybackRegion::getRangeInAudioSource() const
{
	return mRangeInAudioSource;
}
