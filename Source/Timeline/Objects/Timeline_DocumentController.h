#pragma once
#include "Util/Juce_Header.h"

namespace Timeline
{

class Document;
class AudioSource;
class RegionSequence;
class PlaybackRegion;

/*
 Unlike the Timeline::AudioSource/PlaybackRegion/AudioMod etc. this is not meant to be inherited from by an ARADocumentSpecialisation
 
 The goal is to have Timeline::Document match the structure of the ARA::Document in terms of 
 */
class DocumentController
{
public:
	DocumentController();
	~DocumentController();
	
	void addAudioSource(Timeline::AudioSource* source);
	void addRegionSequence(Timeline::RegionSequence* sequence);
	void addPlaybackRegion(Timeline::PlaybackRegion* region);
	
private:
	std::unique_ptr<Timeline::Document> mDocument;
};

}
