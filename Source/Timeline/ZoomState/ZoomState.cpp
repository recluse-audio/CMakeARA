
#include "ZoomState.h"
#include "ZoomStateListener.h"

using namespace Timeline;

//==============
ZoomState::ZoomState()
{
	
}

//==============
ZoomState::~ZoomState()
{
	
}

//=====================================
// SETTERS
//*************************************

//==============
void ZoomState::setSequenceHeight(int sequenceHeight)
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
void ZoomState::setRegionPadding(int regionPadding)
{
	mRegionPadding = regionPadding;
	
	sendChangeMessage();
}

//==============
void ZoomState::setPixelsPerSecond(int pixPerSecond)
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

//=============
void ZoomState::setSampleRate(double sampleRate)
{
	mSampleRate = sampleRate;
}


//=====================================
// GETTERS
//*************************************

//==============
int ZoomState::getSequenceHeight()
{
	return (int)mSequenceHeight.load();
}

//==============
int ZoomState::getRegionPadding()
{
	return mRegionPadding.load();
}

//==============
int ZoomState::getPixelsPerSecond()
{
	return (int)mPixelsPerSecond.load();
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

//==============
double ZoomState::getSampleRate()
{
	return mSampleRate.load();
}





//=============
int ZoomState::getValidHeight(int height)
{
	auto minHeight = minZoom * baseSequenceHeight;
	auto maxHeight = maxZoom * baseSequenceHeight;
	auto validHeight = juce::jlimit(minHeight, maxHeight, (double)height);
	return validHeight;
}

//=============
int ZoomState::getValidPixelsPerSecond(int pixPerSecond)
{
	auto minPix = minZoom * basePixelsPerSecond;
	auto maxPix = maxZoom * basePixelsPerSecond;
	auto validPix = juce::jlimit(minPix, maxPix, (double)pixPerSecond);
	return validPix;
}


//=============
void ZoomState::addZoomStateListener(Timeline::ZoomStateListener* listener)
{
	this->addChangeListener(listener);
}

//=============
void ZoomState::removeZoomStateListener(Timeline::ZoomStateListener *listener)
{
	this->removeChangeListener(listener);
}
