
#include "ZoomState.h"

using namespace Timeline;

//==============
ZoomState::ZoomState()
{
	
}

//==============
ZoomState::~ZoomState()
{
	
}

//==============
void ZoomState::setSequenceHeight(double sequenceHeight)
{
	// Keep within limits of min/max zoom
	auto validHeight = getValidHeight(sequenceHeight);
	mSequenceHeight = validHeight;
	
	// update zoom factor accordingly
	mHeightFactor = mSequenceHeight / baseSequenceHeight;
	
	// tell ZoomStateListeners to 'updateZoomState()'
	sendChangeMessage();
}

//==============
void ZoomState::setPixelsPerSecond(double pixPerSecond)
{
	// Keep within limits of min/max zoom
	auto validPix = getValidPixelsPerSecond(pixPerSecond);
	mPixelsPerSecond = validPix;
	
	// update zoom factor accordingly
	mWidthFactor = mPixelsPerSecond / basePixelsPerSecond;
	
	// tell ZoomStateListeners to 'updateZoomState()'
	sendChangeMessage();

}

//==============
void ZoomState::setHeightZoomFactor(double zoomFactor)
{
	// Keep within limits of min/max zoom
	auto validZoom = juce::jlimit(minZoom, maxZoom, zoomFactor);
	mHeightFactor = validZoom;
	
	// update mSequenceHeight accordingly
	mSequenceHeight = baseSequenceHeight * mHeightFactor;
	
	// tell ZoomStateListeners to updateZoomState
	sendChangeMessage();
}

//==============
void ZoomState::setWidthZoomFactor(double zoomFactor)
{
	auto validZoom = juce::jlimit(minZoom, maxZoom, zoomFactor);
	mWidthFactor = validZoom;
	
	mPixelsPerSecond = basePixelsPerSecond * mWidthFactor;
	
	sendChangeMessage();

}

//==============
double ZoomState::getSequenceHeight()
{
	return mSequenceHeight.load();
}

//==============
double ZoomState::getPixelsPerSecond()
{
	return mPixelsPerSecond.load();
}

//==============
double ZoomState::getHeightZoomFactor()
{
	return mHeightFactor.load();
}

//==============
double ZoomState::getWidthZoomFactor()
{
	return mWidthFactor.load();
}





//=============
double ZoomState::getValidHeight(double height)
{
	auto minHeight = minZoom * baseSequenceHeight;
	auto maxHeight = maxZoom * baseSequenceHeight;
	auto validHeight = juce::jlimit(minHeight, maxHeight, height);
	return validHeight;
}

//=============
double ZoomState::getValidPixelsPerSecond(double pixPerSecond)
{
	auto minPix = minZoom * basePixelsPerSecond;
	auto maxPix = maxZoom * basePixelsPerSecond;
	auto validPix = juce::jlimit(minPix, maxPix, pixPerSecond);
	return validPix;
}



