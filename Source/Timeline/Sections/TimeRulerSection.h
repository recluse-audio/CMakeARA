#pragma once
#include <Util/Juce_Header.h>

class TimeRulerSection : public juce::Component
{
public:
	TimeRulerSection();
	~TimeRulerSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	
};
