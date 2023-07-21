#pragma once
#include <Util/Juce_Header.h>
#include "ViewportSection.h"

namespace Timeline
{


class TimeRulerView;

/**
	Holds viewport and scrolls across TimeRulerView
*/
class TimeRulerSection : public Timeline::ViewportSection
{
public:
	TimeRulerSection(Timeline::ZoomState& zoomState);
	~TimeRulerSection() override;
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	// Calls juce::Viewport function of the same name
	void setViewPosition(int x, int y);
private:
	std::unique_ptr<TimeRulerView> mTimeRuler;
};

}
