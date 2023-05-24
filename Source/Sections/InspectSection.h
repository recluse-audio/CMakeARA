#pragma once

#include <Util/Juce_Header.h>


class InspectSection : public juce::Component
{
public:
	InspectSection();
	~InspectSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
private:

};



