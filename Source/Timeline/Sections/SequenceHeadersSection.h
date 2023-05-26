#pragma once
#include <Util/Juce_Header.h>

class SequenceHeaderView;

class SequenceHeadersSection : public juce::Component
{
public:
	SequenceHeadersSection();
	~SequenceHeadersSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	std::unique_ptr<juce::Viewport> mViewport;
	std::unique_ptr<SequenceHeaderView> mSequenceHeaderView;
	
	
};

