#include "ViewportSection.h"
#include "../ZoomState/ZoomState.h"
#include "../ZoomState/ZoomStateListener.h"

using namespace Timeline;

ViewportSection::ViewportSection(Timeline::ZoomState& zoomState) : mZoomState(zoomState)
{
	mViewport = std::make_unique<juce::Viewport>();
	addAndMakeVisible(*mViewport.get());
}

ViewportSection::~ViewportSection()
{
	
}

juce::Viewport* ViewportSection::getViewport()
{
	return mViewport.get();
}


//==============
void ViewportSection::resized()
{
	auto bounds = this->getLocalBounds();
	mViewport->setBounds(bounds);
}


//==============
void ViewportSection::setZoomStateToFollow(Timeline::ZoomState& zoomState)
{
	auto viewedComponent = mViewport->getViewedComponent();
	
	// Add viewed component as listener if it is a ZoomStateListener
	if(auto zoomListener = dynamic_cast<Timeline::ZoomStateListener*>(viewedComponent))
		zoomState.addZoomStateListener(zoomListener);
	
	for(int i = 0; i < viewedComponent->getNumChildComponents(); i++)
	{
		auto childComponent = viewedComponent->getChildComponent(i);
		if(auto zoomListener = dynamic_cast<Timeline::ZoomStateListener*>(childComponent))
			zoomState.addZoomStateListener(zoomListener);
	}
}
