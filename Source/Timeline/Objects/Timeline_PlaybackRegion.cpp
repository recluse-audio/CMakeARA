#include "Timeline_PlaybackRegion.h"
#include "Timeline_AudioModification.h"
#include "Timeline_AudioSource.h"

using namespace Timeline;

//=============================
PlaybackRegion::PlaybackRegion(Timeline::AudioSource& audioSource, Timeline::AudioModification& audioMod)
: mAudioSource(audioSource)
, mAudioMod(audioMod)
{
	
}


//=============================
PlaybackRegion::~PlaybackRegion()
{

}


//=============================
PlaybackRegion::RenderRanges PlaybackRegion::getRenderRanges(juce::Range<juce::int64> blockRangeInTimeline)
{
	auto regionRangeInTimeline = getRangeInTimeline();
	auto regionRangeInAudioSource = getRangeInAudioSource();
	
	RenderRanges renderRanges;
	renderRanges.rangeInTimeline = calculateRangeToRenderInTimeline(blockRangeInTimeline, regionRangeInTimeline);
	renderRanges.rangeInBlock = calculateRangeToRenderInBlock(blockRangeInTimeline, renderRanges.rangeInTimeline);

	renderRanges.rangeInAudioSource = calculateRangeToReadInAudioSource(blockRangeInTimeline, regionRangeInTimeline, regionRangeInAudioSource);
	
	return renderRanges;
}




//=============================
juce::Range<juce::int64> PlaybackRegion::calculateRangeToRenderInBlock(juce::Range<juce::int64> fullBlockRangeInTimeline, juce::Range<juce::int64> rangeToRenderInTimeline)
{
	auto startInBlock = rangeToRenderInTimeline.getStart() - fullBlockRangeInTimeline.getStart();
	auto range = fullBlockRangeInTimeline.getIntersectionWith(rangeToRenderInTimeline).movedToStartAt(startInBlock);
	return range;
}

//=============================
juce::Range<juce::int64> PlaybackRegion::calculateRangeToRenderInTimeline(juce::Range<juce::int64> blockRange,
															juce::Range<juce::int64> regionRangeInTimeline)
{
	auto rangeToRead = blockRange;
	
	rangeToRead = rangeToRead.getIntersectionWith(regionRangeInTimeline);
	
	return rangeToRead;
}



//=========================
juce::Range<juce::int64> PlaybackRegion::calculateRangeToReadInAudioSource(juce::Range<juce::int64> blockRangeInTimeline,
															juce::Range<juce::int64> regionRangeInTimeline,
															juce::Range<juce::int64> regionRangeInSource)
{

	juce::Range<juce::int64> rangeToRead;

	// Should be same length, the offset is what matters
	if(regionRangeInTimeline.getLength() != regionRangeInSource.getLength())
		return rangeToRead;
	
	rangeToRead = calculateRangeToRenderInTimeline(blockRangeInTimeline, regionRangeInTimeline);

	auto readOffset = calculateAudioSourceReadOffset(regionRangeInTimeline.getStart(), regionRangeInSource.getStart());
	auto rangeToReadStart = rangeToRead.getStart() + readOffset;
	auto rangeToReadEnd = rangeToReadStart + rangeToRead.getLength();
	
	// don't read past end of audio source / playback region
	if(rangeToReadEnd > regionRangeInSource.getEnd())
		rangeToReadEnd = regionRangeInSource.getEnd();
	
	rangeToRead.setStart(rangeToReadStart);
	rangeToRead.setEnd(rangeToReadEnd);
	
	return rangeToRead;
}

/** Calculates the offset*/
juce::int64 PlaybackRegion::calculateAudioSourceReadOffset(juce::int64 regionStartInTimeline,
												  juce::int64 regionStartInAudioSource)
{
	auto offset = regionStartInAudioSource - regionStartInTimeline;
	return offset;
}






//==============================
Timeline::AudioSource* PlaybackRegion::getAudioSource() const
{
	return &mAudioSource;
}