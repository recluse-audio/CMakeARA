#pragma once
#include <Util/Juce_Header.h>

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
private:
	std::unique_ptr<juce::Viewport> mViewport;
	std::unique_ptr<TimeRulerView> mTimeRuler;
};
