#pragma once
#include "Util/Juce_Header.h"

class AudioMod_AudioProcessor;


/**
	This class represents a shared parameter state or "modification" that is shared by one or more playback regions.
	Also can exist with no regions and wait for regions to be assigned to it.
*/
namespace Timeline
{

class AudioSource;
class PlaybackRegion;

class AudioModification
{
public:
	AudioModification();
	~AudioModification();
	
	void generateRandomColor();
	
	juce::Colour getColor() const;
	
	juce::AudioProcessorValueTreeState& getValueTreeState();

	float getParameterValue(juce::Identifier paramID) const;
	
	void setSelected(bool shouldBeSelected);
	
	// Return your custom ARA::AudioSource that also inherits from Timeline::AudioSource
	// Or, return your Test::AudioSource that also inherits from Timeline::AudioSource
	virtual Timeline::AudioSource* getAudioSource() = 0;
	
	// Return a vector of your custom ARA::PlaybackRegion that also inherits from Timeline::PlaybackRegion
	// Or, return your Test::PlaybackRegion that also inherits from Timeline::PlaybackRegion
	virtual std::vector<Timeline::PlaybackRegion*> getPlaybackRegions() = 0;
	
private:
	std::unique_ptr<AudioMod_AudioProcessor> processor;
};

}
