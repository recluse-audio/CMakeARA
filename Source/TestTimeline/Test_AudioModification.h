//
//
//#pragma once
//#include "Util/Juce_Header.h"
//#include "Timeline/Timeline_AudioModification.h"
//#include "Timeline/Timeline_AudioSource.h"
//#include "Timeline/Timeline_PlaybackRegion.h"
//
//
//namespace Test
//{
///**
//	An easy to instantiate version of the Timeline::AudioModification base class that I will use for testing purposes
// 
// */
//class AudioModification : public Timeline::AudioModification
//{
//public:
//	using Int64Range = juce::Range<juce::int64>;
//	
//	AudioModification()
//	{
//	}
//	
//	~AudioModification()
//	{
//	}
//	
//	void setAudioSource(Timeline::AudioSource* audioSource)
//	{
//		mAudioSource.reset(audioSource);
//	}
//	
//	void addPlaybackRegion(Timeline::PlaybackRegion* playbackRegion)
//	{
//		mPlaybackRegions.push_back(playbackRegion);
//	}
//	
////	Timeline::AudioSource* getAudioSource() override
////	{
////		return mAudioSource.get();
////	}
////
////	const std::vector<Timeline::PlaybackRegion*>& getPlaybackRegions() override
////	{
////		return mPlaybackRegions;
////	}
////
//
//private:
//	std::unique_ptr<Timeline::AudioSource> mAudioSource;
//	std::vector<Timeline::PlaybackRegion*> mPlaybackRegions;
//};
//
//}
