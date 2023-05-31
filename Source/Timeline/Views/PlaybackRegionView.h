
#pragma once
#include <Util/Juce_Header.h>

class PlaybackRegionView : public juce::Component
{
public:
	PlaybackRegionView();
	~PlaybackRegionView() override;
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
private:
	
};

