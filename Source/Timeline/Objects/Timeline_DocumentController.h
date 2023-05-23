#pragma once
#include "Util/Juce_Header.h"

namespace Timeline
{

/*
 Unlike the Timeline::AudioSource/PlaybackRegion/AudioMod etc. this is not meant to be inherited from by an ARADocumentSpecialisation
 
 The goal is to have Timeline::Document match the structure of the ARA::Document in terms of 
 */
class DocumentController
{
public:
	DocumentController();
	~DocumentController();
	
};

}
