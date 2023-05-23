
#include "PlaybackRegionView.h"
#include "../WaveCache/WaveformCache.h"

PlaybackRegionView::PlaybackRegionView(juce::AudioThumbnail& thumbnail, juce::ARAPlaybackRegion* pRegion)
: audioThumbnail(thumbnail)
{
	auto audioSource = pRegion->getAudioModification()->getAudioSource();
	sourceDuration = audioSource->getDuration();
}

PlaybackRegionView::~PlaybackRegionView()
{
	
}

void PlaybackRegionView::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::darkred);
	auto bounds = this->getLocalBounds();

	// Draw full audio source
	g.setColour (juce::Colours::whitesmoke.darker().withAlpha(0.3f));
	audioThumbnail.drawChannels (g, bounds, 0, sourceDuration, 1.0f);
}

void PlaybackRegionView::resized()
{
	
}
