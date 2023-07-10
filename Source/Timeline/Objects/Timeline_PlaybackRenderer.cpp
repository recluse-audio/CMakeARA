#include "Timeline_PlaybackRenderer.h"
#include "Timeline_PlaybackRegion.h"

using namespace Timeline;

PlaybackRenderer::PlaybackRenderer()
{
	
}

PlaybackRenderer::~PlaybackRenderer()
{
	
}

void PlaybackRenderer::processBlock(juce::AudioBuffer<float>& block)
{

}

void PlaybackRenderer::addPlaybackRegion(Timeline::PlaybackRegion* pRegion)
{
    mPlaybackRegions.push_back(pRegion);
}

int PlaybackRenderer::getNumRegions()
{
    return (int)mPlaybackRegions.size();
}