#pragma once
#include <Util/Juce_Header.h>
#include "ViewportSection.h"

namespace Timeline
{

class ZoomState;

class SequenceHeaderView;

class SequenceHeadersSection : public Timeline::ViewportSection
{
public:
	SequenceHeadersSection(Timeline::ZoomState& zoomState);
	~SequenceHeadersSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	// Calls juce::Viewport function of the same name
	void setViewPosition(int x, int y);
	
private:
	std::unique_ptr<SequenceHeaderView> mSequenceHeaderView;
	
	
};

}
