
#pragma once
#include "../../Util/Juce_Header.h"

namespace Timeline
{

class ZoomState;

/**
	This class owns a viewport and can return one if you ask

	Each TimelineSection will inherit from this
 
	While the viewport component will resize according to zoom state, this will not
 
*/
class ViewportSection : public juce::Component
{
public:
	
	ViewportSection(Timeline::ZoomState& zoomState);
	
	~ViewportSection();
	
	void resized() override;
	
	juce::Viewport* getViewport();
	
	// TODO: this is testable behavior
	void setZoomStateToFollow(Timeline::ZoomState& zoomState);
	
protected:
	Timeline::ZoomState& mZoomState;
	
	std::unique_ptr<juce::Viewport> mViewport;
};

}
