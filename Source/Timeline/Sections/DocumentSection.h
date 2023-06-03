
#pragma once
#include <Util/Juce_Header.h>

namespace Timeline
{


class DocumentView;

class DocumentSection : public juce::Component
{
public:
	DocumentSection();
	~DocumentSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	// This is the "master" viewport.  timeruler and sequence headers need to follow this
	juce::Viewport* getViewport();
	
private:
	std::unique_ptr<juce::Viewport> mViewport;
	std::unique_ptr<Timeline::DocumentView> mDocumentView;
};

}
