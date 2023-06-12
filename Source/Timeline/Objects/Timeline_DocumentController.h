#pragma once
#include "Util/Juce_Header.h"

namespace Timeline
{

class Document;
class AudioSource;
class RegionSequence;
class PlaybackRegion;

/*
 Unlike the Timeline::AudioSource/PlaybackRegion/AudioMod etc. this is not meant to be inherited from by an ARADocumentSpecialisation, but rather owned by it.
 
	Our ARADocumentSpecialisation will 

 */
class DocumentController
{
public:
	DocumentController();
	~DocumentController();
	
	void addRegionSequence(Timeline::RegionSequence* sequence);
	
private:
	std::unique_ptr<Timeline::Document> mDocument;
};

}
