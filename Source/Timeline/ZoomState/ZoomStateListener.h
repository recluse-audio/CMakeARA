/*
  ==============================================================================

	ZoomStateListener.h
	Created: 31 Jan 2023 5:00:25pm
	Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include "../Util/Juce_Header.h"
#include "ZoomState.h"

namespace Timeline
{


class ZoomStateListener : public juce::ChangeListener
{
public:
	ZoomStateListener(Timeline::ZoomState& zoomStateToFollow)
	: mZoomState(zoomStateToFollow)
	{
		
	}
	
	void changeListenerCallback(juce::ChangeBroadcaster* source) override
	{
		auto zoomState = dynamic_cast<Timeline::ZoomState*>(source);
		if(zoomState != nullptr)
			updateZoomState(zoomState);
	}
	
	virtual void updateZoomState(Timeline::ZoomState* zoomState) = 0;

	Timeline::ZoomState& getZoomState() const
	{
		return mZoomState;
	}
	
	
private:
	Timeline::ZoomState& mZoomState;
	
};

}
