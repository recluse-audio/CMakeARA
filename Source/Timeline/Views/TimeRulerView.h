
#pragma once
#include <Util/Juce_Header.h>

namespace Timeline
{


class TimeRulerView : public juce::Component
{
public:
	TimeRulerView();
	~TimeRulerView() override;
	
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	
};

}
