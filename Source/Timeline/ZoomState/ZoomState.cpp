
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
	auto validHeight = getValidHeight(sequenceHeight);
	mSequenceHeight = validHeight;
	sendChangeMessage();
}

//==============
void ZoomState::setPixelsPerSecond(double pixPerSecond)
{
	auto validPix = getValidPixelsPerSecond(pixPerSecond);
	mPixelsPerSecond = validPix;
	sendChangeMessage();

}

//==============
void ZoomState::setHeightZoomFactor(double zoomFactor)
{
	auto validZoom = juce::jlimit(minZoom, maxZoom, zoomFactor);
	mHeightFactor = validZoom;
	sendChangeMessage();
}

//==============
void ZoomState::setWidthZoomFactor(double zoomFactor)
{
	auto validZoom = juce::jlimit(minZoom, maxZoom, zoomFactor);
	mWidthFactor = validZoom;
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



