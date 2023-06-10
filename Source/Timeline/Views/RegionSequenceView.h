#pragma once
#include "Util/Juce_Header.h"
#include "../ZoomState/ZoomStateListener.h"


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
, public Timeline::ZoomStateListener
{
public:
	RegionSequenceView(Timeline::RegionSequence& sequence);
	~RegionSequenceView();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	void updateZoomState(Timeline::ZoomState* zoomState) override;
	
	/** Adds this RegionSequenceView and its child PlaybackRegionViews to follow the given ZoomState*/
	void setZoomStateToFollow(Timeline::ZoomState* zoomState);

	
private:
	Timeline::RegionSequence& mRegionSequence;
	juce::OwnedArray<Timeline::PlaybackRegionView> mPlaybackRegionViews;
	
	void createPlaybackRegionView(Timeline::PlaybackRegion* pRegion);

};

}
