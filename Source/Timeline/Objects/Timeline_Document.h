#pragma once
#include "../Util/Juce_Header.h"

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

class Document
{
public:
	static constexpr auto minTimelineLength = 120.0;
	
	Document();
	Document(const Document& other);
	~Document();
	
	void addRegionSequence(Timeline::RegionSequence* pSequence);
	std::vector<Timeline::RegionSequence*> getRegionSequences();

	
	void setPlaybackSampleRate(double sampleRate);
	double getPlaybackSampleRate() const;
	
	// Returns the longest sequence duration in seconds or 120 seconds minimum
	double getTimelineLength() const;
	int getNumSequences() const;
private:
	std::vector<Timeline::RegionSequence*> mRegionSequences;
	double mPlaybackSampleRate = 44100;


	
};

}
