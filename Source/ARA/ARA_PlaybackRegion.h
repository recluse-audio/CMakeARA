/*
  ==============================================================================

    ARA_PlaybackRegion.h
    Created: 26 Nov 2022 12:15:41pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <../Util/Juce_Header.h>


class ARA_PlaybackRegion : public juce::ARAPlaybackRegion
{
public:
  using juce::ARAPlaybackRegion::ARAPlaybackRegion;
	juce::Range<juce::int64> getRangeToReadInAudioSource(juce::Range<juce::int64> blockRange);
	
	
private:

// Given a block range calculates if and where it overlaps with a playback region, returns the appropriate chunk of playback region's audio source
	static juce::Range<juce::int64> _calculateRangeOverlapping(juce::Range<juce::int64> blockRange, juce::Range<juce::int64> regionRange, juce::Range<juce::int64> modRange)
  {
    
  }
    
    
};
