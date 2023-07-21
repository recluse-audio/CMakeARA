
#pragma once
#include <Util/Juce_Header.h>
#include "ViewportSection.h"


namespace Timeline
{

class Document;
class DocumentView;

class DocumentSection : public Timeline::ViewportSection
{
public:
	DocumentSection(Timeline::ZoomState& zoomState);
	~DocumentSection() override;
	
	void paint(juce::Graphics& g) override;
	void resized() override;

	void loadDocument(Timeline::Document& document);
	
private:
	std::unique_ptr<Timeline::DocumentView> mDocumentView;
	
	

};

}
