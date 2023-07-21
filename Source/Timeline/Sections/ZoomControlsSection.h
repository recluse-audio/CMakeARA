#pragma once
#include <Util/Juce_Header.h>
#include "Timeline/ZoomState/ZoomState.h"

namespace Timeline
{

// class ZoomControls;

class ZoomControlsSection : public juce::Component
                    , public juce::Button::Listener
{
public:
	ZoomControlsSection(Timeline::ZoomState& zoomState);
	~ZoomControlsSection() override;
	
	void paint(juce::Graphics& g) override;
	void resized() override;
    void buttonClicked(juce::Button* b) override;

private:
    Timeline::ZoomState& mZoomState;
    std::unique_ptr<juce::TextButton> mZoomInButton;
    std::unique_ptr<juce::TextButton> mZoomOutButton;
	
};

}
