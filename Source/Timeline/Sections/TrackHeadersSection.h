#pragma once
#include <Util/Juce_Header.h>

class TrackHeadersSection : public juce::Component
{
public:
	TrackHeadersSection();
	~TrackHeadersSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	
};

