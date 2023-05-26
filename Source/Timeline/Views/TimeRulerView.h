
#pragma once
#include <Util/Juce_Header.h>

class TimeRulerView : public juce::Component
{
public:
	TimeRulerView();
	~TimeRulerView();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	
};
