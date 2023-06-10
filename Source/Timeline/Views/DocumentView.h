
#pragma once
#include <Util/Juce_Header.h>
#include "../ZoomState/ZoomStateListener.h"

namespace Timeline
{


class RegionSequenceView;
class PlaybackRegion;
class RegionSequence;

class DocumentView : public juce::Component
, public Timeline::ZoomStateListener
{
public:
	DocumentView();
	~DocumentView();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	// Adds RegionSequenceView for given RegionSequence
	void addRegionSequence(Timeline::RegionSequence& pSequence);
	
	// clears all views associated with TimelineObjects / Document
	void addRegionSequences(std::vector<Timeline::RegionSequence*> sequences);
	
	void resetTimeline();
	
	void updateZoomState(Timeline::ZoomState* zoomState) override;
	
	void setZoomStateToFollow(Timeline::ZoomState* zoomState);
	
private:
	juce::OwnedArray<Timeline::RegionSequenceView>	mRegionSequences;
};

}
