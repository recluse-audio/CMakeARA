#pragma once

#include <Util/Juce_Header.h>


class NavigationSection : public juce::Component
{
public:
	NavigationSection();
	~NavigationSection() override;
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
private:

};

