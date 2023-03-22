#include <catch2/catch_test_macros.hpp>
#include "MultiTrackTimeline/Timeline_PlaybackRegion.h"
#include "MultiTrackTimeline/Timeline_AudioSource.h"

using namespace Timeline;

TEST_CASE("PlaybackRegion::getRangeInTimelineSeconds()")
{
	juce::AudioBuffer<float> bufferSource(1, 100);
	AudioSource audioSource(bufferSource);

	PlaybackRegion::PositionInfo posInfo;
	posInfo.startInTimeline = 10;
	posInfo.startInAudioSource = 10;
	posInfo.duration = 20;
	
	PlaybackRegion region(posInfo, audioSource);

	SECTION("Should match juce::Range passed into constructor")
	{
		auto rangeInTimeline = region.getRangeInTimeline();
		CHECK(rangeInTimeline.getStart() == posInfo.startInTimeline);
		CHECK(rangeInTimeline.getEnd() == posInfo.startInTimeline + posInfo.duration);
		
		auto rangeInAudioSource = region.getRangeInAudioSource();
		CHECK(rangeInAudioSource.getStart() == posInfo.startInAudioSource);
		CHECK(rangeInAudioSource.getEnd() == posInfo.startInAudioSource + posInfo.duration);
	}
}
