#include "Timeline_PlaybackRegion.h"
#include "Timeline_AudioSource.h"

using namespace Timeline;

PlaybackRegion::RenderRanges PlaybackRegion::getRenderRanges(juce::Range<juce::int64> blockRange)
{
	auto regionRangeInTimeline = getRangeInTimeline();
	auto regionRangeInAudioSource = getRangeInAudioSource();
	
	RenderRanges renderRanges;
	renderRanges.blockRangeToRender = calculateBlockRangeToRender(blockRange, regionRangeInTimeline);
	renderRanges.audioSourceRangeToRead = calculateRangeToReadInAudioSource(blockRange, regionRangeInTimeline, regionRangeInAudioSource);
	
	return renderRanges;
}

/** Give a block range, this tells you which portion overlaps with a playback region */
juce::Range<juce::int64> PlaybackRegion::calculateBlockRangeToRender(juce::Range<juce::int64> blockRange,
															juce::Range<juce::int64> regionRangeInTimeline)
{
	auto rangeToRead = blockRange;
	
	rangeToRead = rangeToRead.getIntersectionWith(regionRangeInTimeline);
	
	// Don't waste our time if no overlap with region
	if(rangeToRead.isEmpty())
		return rangeToRead;
	
	
	return rangeToRead;
	
}



/**
	This function takes the range of the start / end position of a process block
	and returns the range of an audio source should be read for this region given
	the timeline position of the process block
*/
juce::Range<juce::int64> PlaybackRegion::calculateRangeToReadInAudioSource(juce::Range<juce::int64> blockRangeInTimeline,
															juce::Range<juce::int64> regionRangeInTimeline,
															juce::Range<juce::int64> regionRangeInSource)
{

	juce::Range<juce::int64> rangeToRead;

	// Should be same length, the offset is what matters
	if(regionRangeInTimeline.getLength() != regionRangeInSource.getLength())
		return rangeToRead;
	
	rangeToRead = calculateBlockRangeToRender(blockRangeInTimeline, regionRangeInTimeline);

	auto readOffset = calculateAudioSourceReadOffset(regionRangeInTimeline.getStart(), regionRangeInSource.getStart());
	auto rangeToReadStart = blockRangeInTimeline.getStart() + readOffset;
	auto rangeToReadEnd = rangeToReadStart + blockRangeInTimeline.getLength();
	
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

