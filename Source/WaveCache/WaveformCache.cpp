/*
  ==============================================================================

	WaveformCache.cpp
	Created: 2 Nov 2022 12:21:53pm
	Author:  Ryan Devens

  ==============================================================================
*/

#include "WaveformCache.h"

WaveformCache::WaveformCache() : thumbnailCache (20)
{
}

WaveformCache::~WaveformCache()
{
//	for (const auto& entry : thumbnails)
//	{
//		entry.first->removeListener (this);
//	}
}

//
juce::AudioThumbnail& WaveformCache::getOrCreateThumbnail (juce::ARAAudioSource* audioSource)
{
	const auto iter = thumbnails.find (audioSource);

	if (iter != std::end (thumbnails))
		return *iter->second;

	auto thumb = std::make_unique<juce::AudioThumbnail> (128, dummyManager, thumbnailCache);
	auto& result = *thumb;

	++hash;
	thumb->setReader (new juce::ARAAudioSourceReader (audioSource), hash);

	//audioSource->addListener (this);
	thumbnails.emplace (audioSource, std::move (thumb));
	return result;
}


juce::AudioThumbnail& WaveformCache::getOrCreateThumbnail (AudioData* audioData)
{
	const auto iter = audioThumbnails.find (audioData);

	if (iter != std::end (audioThumbnails))
		return *iter->second;


}






//


//==============================================================================
//void WaveformCache::willDestroyAudioSource (juce::ARAAudioSource* audioSource)
//{
//	removeAudioSource (audioSource);
//}

//
//
//======================
// PRIVATE FUNCTIONS

void WaveformCache::removeAudioSource (juce::ARAAudioSource* audioSource)
{
//	audioSource->removeListener (this);
	thumbnails.erase (audioSource);
}
//
