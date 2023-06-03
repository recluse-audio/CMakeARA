#pragma once
#include <Util/Juce_Header.h>

namespace Timeline
{


class TimeRulerView;

/**
	Holds viewport and scrolls across TimeRulerView
*/
class TimeRulerSection : public juce::Component
{
public:
	TimeRulerSection();
	~TimeRulerSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	// Calls juce::Viewport function of the same name
	void setViewPosition(int x, int y);
private:
	std::unique_ptr<juce::Viewport> mViewport;
	std::unique_ptr<TimeRulerView> mTimeRuler;
};

}
