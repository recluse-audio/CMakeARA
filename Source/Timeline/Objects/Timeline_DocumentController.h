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
	
	// You'd better be able to make a Timeline::Document in your subclass one way or another!
	virtual Timeline::Document& getTimelineDocument() const = 0;
	
private:

};

}
