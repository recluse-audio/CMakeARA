
#pragma once
#include <Util/Juce_Header.h>

class DocumentView;

class DocumentSection : public juce::Component
{
public:
	DocumentSection();
	~DocumentSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	std::unique_ptr<juce::Viewport> mViewport;
	std::unique_ptr<DocumentView> mDocumentView;
};
