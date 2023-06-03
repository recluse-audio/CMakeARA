#pragma once
#include <Util/Juce_Header.h>

namespace Timeline
{


class SequenceHeaderView;

class SequenceHeadersSection : public juce::Component
{
public:
	SequenceHeadersSection();
	~SequenceHeadersSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	// Calls juce::Viewport function of the same name
	void setViewPosition(int x, int y);
	
private:
	std::unique_ptr<juce::Viewport> mViewport;
	std::unique_ptr<SequenceHeaderView> mSequenceHeaderView;
	
	
};

}
