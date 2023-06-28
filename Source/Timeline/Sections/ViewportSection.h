
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
	
	// All child components of the viewed component that are ZoomStateListeners will listen to this ZoomState
	void setZoomStateToFollow(Timeline::ZoomState& zoomState);
	
	// Stops child components from listening to the zoom state
	void removeZoomStateListeners();
	
protected:
	Timeline::ZoomState& mZoomState;
	
	std::unique_ptr<juce::Viewport> mViewport;
};

}
