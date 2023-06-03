#pragma once
#include <Util/Juce_Header.h>

namespace Timeline
{


class ZoomControlsSection : public juce::Component
{
public:
	ZoomControlsSection();
	~ZoomControlsSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	
};

}
