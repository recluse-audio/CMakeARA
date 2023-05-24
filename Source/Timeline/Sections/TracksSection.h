
#pragma once
#include <Util/Juce_Header.h>

class TracksSection : public juce::Component
{
public:
	TracksSection();
	~TracksSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	
};
