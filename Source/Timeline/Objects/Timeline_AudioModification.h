#pragma once
#include "Util/Juce_Header.h"



/**
	This class represents a shared parameter state or "modification" that is shared by one or more playback regions.
	Also can exist with no regions and wait for regions to be assigned to it.
 
*/
namespace Timeline
{

class AudioSource;
class PlaybackRegion;
class ModificationProcessor;

class AudioModification
{
public:
	// have to pass undoManager ref here to get benefits of valueTreeState :/
	AudioModification(juce::UndoManager& undoManagerRef);
	~AudioModification();
	
	static juce::Colour generateRandomColour();
	
	juce::Colour getColour() const;
	
	juce::AudioProcessorValueTreeState& getValueTreeState();
	// This is risky to call if the same parameter is attached to automation or GUI
	void setParameterValue(juce::Identifier paramID, float value);
	float getParameterValue(juce::Identifier paramID) const;
		
	
//	// Return your custom ARA::AudioSource that also inherits from Timeline::AudioSource
//	// Or, return your Test::AudioSource that also inherits from Timeline::AudioSource
//	virtual Timeline::AudioSource* getAudioSource() = 0;
//
//	// Return a vector of your custom ARA::PlaybackRegion that also inherits from Timeline::PlaybackRegion
//	// Or, return your Test::PlaybackRegion that also inherits from Timeline::PlaybackRegion
//	virtual const std::vector<Timeline::PlaybackRegion*>& getPlaybackRegions() = 0;
	
private:
	std::unique_ptr<Timeline::ModificationProcessor> mProcessor;
	juce::Colour modColour;

};

}
