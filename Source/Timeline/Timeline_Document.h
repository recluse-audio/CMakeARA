#pragma once
#include <Util/Juce_Header.h>

/**
	This class represents all of the objects in a Timeline.  Region Sequences, Audio Modifications, PlaybackRegions...
*/
namespace Timeline
{

class DocumentController;
class AudioSource;

class Document
{
public:
	Document(Timeline::DocumentController* doc);
	~Document();
	
	Timeline::DocumentController* getDocumentController();
	
	void addAudioSource(Timeline::AudioSource source);
	
	std::vector<Timeline::AudioSource> getAudioSources();
private:
	friend class Timeline::DocumentController;
	Timeline::DocumentController* docController;
	
	std::vector<Timeline::AudioSource*> audioSources;
	
};

}
