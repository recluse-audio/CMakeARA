
#pragma once
#include "Util/Juce_Header.h"

namespace Timeline
{
/**
	This class represents the current zoom state of a Timeline.
	It has several functions that handle converting seconds to pixels based on how zoom level
	Similar coverage for calculating sequence (track) height based on the vertical zoom level
*/
class ZoomState : public juce::ChangeBroadcaster
{
public:
	ZoomState();
	~ZoomState();
	
	static constexpr auto minZoom = 1.0;
	static constexpr auto maxZoom = 32.0;
	static constexpr auto baseSequenceHeight = 60.0;  		// Atleast 60 pixels per Region
	static constexpr auto basePixelsPerSecond = 10.0; 	// Atleast 10 pixels per second
	
	
	void setSequenceHeight(double sequenceHeight);
	void setPixelsPerSecond(double pixPerSecond);
	void setHeightZoomFactor(double zoomFactor);
	void setWidthZoomFactor(double zoomFactor);

	
	double getSequenceHeight();
	double getPixelsPerSecond();
	double getHeightZoomFactor();
	double getWidthZoomFactor();
	
	
private:
	// gets a height within the range of the min/max zoom
	double getValidHeight(double height);
	double getValidPixelsPerSecond(double pixPerSecond);
	
	std::atomic<double> mWidthFactor  { minZoom };
	std::atomic<double> mHeightFactor { minZoom };
	std::atomic<double> mSequenceHeight { 60.0 };
	std::atomic<double> mPixelsPerSecond { 10.0 };
};

}
