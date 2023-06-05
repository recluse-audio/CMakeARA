
#pragma once
#include <Util/Juce_Header.h>
#include "../ZoomState/ZoomStateListener.h"

namespace Timeline
{

class PlaybackRegion;

/**
	This class is making the promise that it will update its size properly when zooming in/out
 
 */
class PlaybackRegionView : public juce::Component
, public ZoomStateListener
{
public:
	PlaybackRegionView(Timeline::PlaybackRegion& pRegion);
	~PlaybackRegionView() override;
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	void updateZoomState(ZoomState* zoomState) override;

private:
	// resizes
	void _updateSize(double regionHeight, double pixPerSecond);
	
	Timeline::PlaybackRegion& mPlaybackRegion;
};

}
