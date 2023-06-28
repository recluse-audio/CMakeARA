
#pragma once
#include "Util/Juce_Header.h"

namespace Timeline
{

class ZoomStateListener;
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
	static constexpr auto baseSequenceHeight = 60.0;
	static constexpr auto baseRegionPadding = 2.0; // 2 pixels above/below region in sequence
	static constexpr auto basePixelsPerSecond = 10.0; 	// Atleast 10 pixels per second
	
	
	void setSequenceHeight(double sequenceHeight);
	void setRegionPadding(double regionPadding);
	void setPixelsPerSecond(double pixPerSecond);
	void setHeightZoomFactor(double zoomFactor);
	void setWidthZoomFactor(double zoomFactor);
	void setSampleRate(double sampleRate);
	
	
	int getSequenceHeight();
	double getRegionPadding();
	int getPixelsPerSecond();
	double getHeightZoomFactor();
	double getWidthZoomFactor();
	double getSampleRate();
	
	/** Preferred way of adding ZoomStateListener, as opposed to generic change listener*/
	void addZoomStateListener(Timeline::ZoomStateListener* listener);
	void removeZoomStateListener(Timeline::ZoomStateListener* listener);
	
private:
	// gets a height within the range of the min/max zoom
	double getValidHeight(double height);
	double getValidPadding(double padding);
	double getValidPixelsPerSecond(double pixPerSecond);
	
	std::atomic<double> mWidthFactor  { minZoom };
	std::atomic<double> mHeightFactor { minZoom };
	std::atomic<double> mSequenceHeight { 60.0 };
	std::atomic<double> mRegionPadding { 2.0 };
	std::atomic<double> mPixelsPerSecond { 10.0 };
	std::atomic<double> mSampleRate { 44100.0 };
};

}
