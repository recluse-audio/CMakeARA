#pragma once
#include <Util/Juce_Header.h>

/**
	This class represents the objects in a Timeline.  Region Sequences, Audio Modifications, PlaybackRegions...
*/
namespace Timeline
{

class DocumentController;
class AudioSource;
class AudioModification;
class RegionSequence;
class PlaybackRegion;

class Document
{
public:
	Document(Timeline::DocumentController* doc);
	~Document();
	
	Timeline::DocumentController* getDocumentController();
	

	
	std::vector<Timeline::AudioSource*> audioSources;
	std::vector<Timeline::RegionSequence*> regionSequences;
	std::vector<Timeline::PlaybackRegion*> playbackRegions;

private:
	
	
};

}
