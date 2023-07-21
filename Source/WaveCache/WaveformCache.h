/*
  ==============================================================================

	WaveformCache.h
	Created: 1 Nov 2022 12:47:07pm
	Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <Util/Juce_Header.h>

class AudioData;
//==============================================================================
/**  This class keeps track of AudioData
 
 */
class WaveformCache
{
public:
	WaveformCache();

	~WaveformCache();

//	void willDestroyAudioSource (juce::ARAAudioSource* audioSource) override;

	juce::AudioThumbnail& getOrCreateThumbnail (juce::ARAAudioSource* audioSource);
	



private:
	void removeAudioSource (juce::ARAAudioSource* audioSource);

	juce::int64 hash = 0;
	juce::AudioFormatManager dummyManager;
	juce::AudioThumbnailCache thumbnailCache;
	std::map<juce::ARAAudioSource*, std::unique_ptr<juce::AudioThumbnail>> thumbnails;
	std::map<AudioData*, std::unique_ptr<juce::AudioThumbnail>> audioThumbnails;
	
};

//struct WaveformCache : private juce::ARAAudioSource::Listener
//{
//	WaveformCache();
//
//	~WaveformCache() override;
//
//	//==============================================================================
//	void willDestroyAudioSource (juce::ARAAudioSource* audioSource) override;
//	juce::AudioThumbnail& getOrCreateThumbnail (juce::ARAAudioSource* audioSource);
//
//private:
//	void removeAudioSource (juce::ARAAudioSource* audioSource);
//
//	juce::int64 hash = 0;
//	juce::AudioFormatManager dummyManager;
//	juce::AudioThumbnailCache thumbnailCache;
//	std::map<juce::ARAAudioSource*, std::unique_ptr<AudioThumbnail>> thumbnails;
//};
