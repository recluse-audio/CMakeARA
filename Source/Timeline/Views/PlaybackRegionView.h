
#pragma once
#include <Util/Juce_Header.h>
#include "ObjectView.h"

namespace Timeline
{

class PlaybackRegion;

/**
	This class is making the promise that it will update its size properly when zooming in/out
 
 */
class PlaybackRegionView : public juce::Component
, public Timeline::ObjectView
{
public:
	PlaybackRegionView(Timeline::PlaybackRegion& pRegion, Timeline::ZoomState& zoomState);
	~PlaybackRegionView() override;
	
	void paint(juce::Graphics& g) override;

	// You may want to access the PlaybackRegion to determine start/end time
	const Timeline::PlaybackRegion& getPlaybackRegion() const;
	
private:
	Timeline::PlaybackRegion& mPlaybackRegion;

	// resizes
	void _updateSize() override;
	void _createChildren() override;
	void _positionChildren() override;
	
	
};

}
