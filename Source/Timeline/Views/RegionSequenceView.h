#pragma once
#include "Util/Juce_Header.h"
#include "ObjectView.h"


namespace Timeline
{

class PlaybackRegionView;
class RegionSequence;
class PlaybackRegion;
/**
	Visual representation of a RegionSequence (track).
	I chose to call it RegionSequence instead of 'TrackView' to preserve consistency with the ARA objects
 */
class RegionSequenceView : public juce::Component
, public Timeline::ObjectView
{
public:
	RegionSequenceView(Timeline::RegionSequence& sequence, Timeline::ZoomState& zoomState);
	~RegionSequenceView();
	
	void paint(juce::Graphics& g) override;


	// This returns the x position of the right edge of the last PlaybackRegion in this RegionSequence
	int getEndPositionOfFinalRegion();
	
private:
	Timeline::RegionSequence& mRegionSequence;
	juce::OwnedArray<Timeline::PlaybackRegionView> mPlaybackRegionViews;
	
	
	// updates size of RegionSequenceView according to the ZoomState and the positions of its PlaybackRegions
	void _updateSize() override;
	
	void _createChildren() override;
	
	// Sets the start position of the 
	void _positionChildren() override;
	
	void _createPlaybackRegionView(Timeline::PlaybackRegion* pRegion);

};

}
