
#pragma once
#include <Util/Juce_Header.h>
#include "../ZoomState/ZoomStateListener.h"

namespace Timeline
{

/**
	This class is exists to ensure that the resizing, child creation, and positioning all happen in the right order for Timeline::ObjectViews
	when zooming or refreshing
 
 */
class ObjectView :  public ZoomStateListener
{
public:
	ObjectView(Timeline::ZoomState& zoomState);
	~ObjectView() override;
	
	// ZoomStateListener override
	void updateZoomState(ZoomState* zoomState) override;
	
	/** Updates the size of this view, creates/adds its child views, and positions the child views according to this view's Timeline::Object */
	void refresh();


protected:
	/** Override this function to size your ObjectView according to its children/zoomstate */
	virtual void _updateSize() = 0;
	
	/** Override this function to create all the necessary child views of this ObjectView.  I.e. A RegionSequenceView will make PlaybackRegionView(s) here */
	virtual void _createChildren() = 0;
	
	/** Refers to the child ObjectView components */
	virtual void _positionChildren() = 0;
	
	
};

}

