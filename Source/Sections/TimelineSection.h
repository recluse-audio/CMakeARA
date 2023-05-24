#pragma once
#include <Util/Juce_Header.h>

class TimeRulerSection;
class TrackHeadersSection;
class TracksSection;
class ZoomControlsSection;

class TimelineSection : public juce::Component
{
public:
	TimelineSection();
	~TimelineSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
private:
	std::unique_ptr<TimeRulerSection> 		mTimeRulerSection;
	std::unique_ptr<TrackHeadersSection> 	mTrackHeadersSection;
	std::unique_ptr<TracksSection>			mTracksSection;
	std::unique_ptr<ZoomControlsSection> 	mZoomControlsSection;
	
	
};


