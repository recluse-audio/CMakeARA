/*
  ==============================================================================

    ARA_PlaybackRegion.h
    Created: 26 Nov 2022 12:15:41pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <../Util/Juce_Header.h>
#include "../Timeline/Objects/Timeline_PlaybackRegion.h"

class ARA_AudioSource;
class ARA_AudioModification;

class ARA_PlaybackRegion : public juce::ARAPlaybackRegion
                         , public Timeline::PlaybackRegion
{
public:
  ARA_PlaybackRegion(ARA_AudioSource* audioSource, ARA_AudioModification* audioMod, 
                                         ARA::ARAPlaybackRegionHostRef hostRef);

  juce::Range<double> getRangeInTimelineSeconds() const override;
	juce::Range<juce::int64> getRangeInTimeline() const override; // TODO: Ditch this b/c it depends on sample rate
	juce::Range<juce::int64> getRangeInAudioSource() const override;
private:

    
};
