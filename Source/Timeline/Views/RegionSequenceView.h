#pragma once
#include "Util/Juce_Header.h"

namespace Timeline
{

class PlaybackRegionView;

/**
	Visual representation of a RegionSequence (track).
	I chose to call it RegionSequence instead of 'TrackView' to preserve consistency with the ARA objects
 */
class RegionSequenceView : public juce::Component
{
public:
	RegionSequenceView();
	~RegionSequenceView();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
private:
	std::unique_ptr<Timeline::PlaybackRegionView> mPlaybackRegionView;
};

}
