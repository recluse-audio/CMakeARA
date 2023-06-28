#pragma once
#include <Util/Juce_Header.h>

/**
	This class represents an object that will be owned by an ARADocumentControllerSpecialisation.
	
	It should remain a minimalist abstraction of the ARA things we need for drawing and interaction.
 
	This assumes Timeline::Objects are organized in the right arrangment.  Timeline::RegionSequences already have the correct PlaybackRegions added.  PlaybackRegions have all the pointers they will need, etc...
*/
namespace Timeline
{

class DocumentController;
class AudioSource;
class AudioModification;
class RegionSequence;
class PlaybackRegion;

class Document final
{
public:
	Document();
	~Document();
	
	void addRegionSequence(Timeline::RegionSequence* pSequence);
	std::vector<Timeline::RegionSequence*> getRegionSequences();
	
	void setPlaybackSampleRate(double sampleRate);
	double getPlaybackSampleRate() const;
	
	// Returns the longest sequence duration in seconds
	double getLongestSequenceInSeconds() const;
	int getNumSequences() const;
private:
	std::vector<Timeline::RegionSequence*> mRegionSequences;
	double mPlaybackSampleRate = 44100;
	
};

}
