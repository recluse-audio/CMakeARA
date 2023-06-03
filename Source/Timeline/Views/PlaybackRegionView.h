
#pragma once
#include <Util/Juce_Header.h>
#include "../ZoomState/ZoomStateListener.h"

namespace Timeline
{


class PlaybackRegionView : public juce::Component
, public ZoomStateListener
{
public:
	PlaybackRegionView();
	~PlaybackRegionView() override;
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	void updateZoomState(ZoomState* zoomState) override;

private:
	
};

}
