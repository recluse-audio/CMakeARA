
/*
  ==============================================================================

	PlaybackRegionView.h
	Created: 1 Nov 2022 12:47:47pm
	Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <../Util/Juce_Header.h>

class PluginEditor;
class WaveformCache;

/**
	Simple for now, draws the waveform of an ARA Playback Region
	nada mas
 */
class PlaybackRegionView : public juce::Component
{
public:
	PlaybackRegionView(juce::AudioThumbnail& thumbnail, juce::ARAPlaybackRegion* pRegion);
	~PlaybackRegionView() override;
	
	void paint (juce::Graphics& g) override;
	void resized() override;
	
private:
	juce::AudioThumbnail& audioThumbnail;
	double sourceDuration = 0.0;
};
