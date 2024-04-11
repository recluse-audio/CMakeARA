#include "ARA_PlaybackRegion.h"
#include "ARA_AudioModification.h"
#include "ARA_AudioSource.h"

ARA_PlaybackRegion::ARA_PlaybackRegion(ARA_AudioSource* audioSource, ARA_AudioModification* audioMod, 
                                        ARA::ARAPlaybackRegionHostRef hostRef)
: juce::ARAPlaybackRegion(audioMod, hostRef)
, Timeline::PlaybackRegion(audioSource, audioMod)
{

}

//=======================================
juce::Range<double> ARA_PlaybackRegion::getRangeInTimelineSeconds() const
{
    return this->getTimeRange(IncludeHeadAndTail::no);
}

//=======================================
juce::Range<juce::int64> ARA_PlaybackRegion::getRangeInTimeline() const
{
    // TODO: pass in a real sample rate
    return this->getSampleRange(44100, IncludeHeadAndTail::no);
}

//=======================================
juce::Range<juce::int64> ARA_PlaybackRegion::getRangeInAudioSource() const
{
    // named weird in ARA, this is the call we want
    juce::int64 startSample = this->getStartInAudioModificationSamples();
    juce::int64 endSample = this->getEndInAudioModificationSamples();
    auto range = juce::Range<juce::int64>(startSample, endSample);
    return range;
}