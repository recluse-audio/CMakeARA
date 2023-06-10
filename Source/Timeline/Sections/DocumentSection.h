
#pragma once
#include <Util/Juce_Header.h>
#include "ViewportSection.h"

namespace Timeline
{


class DocumentView;

class DocumentSection : public Timeline::ViewportSection
{
public:
	DocumentSection(Timeline::ZoomState& zoomState);
	~DocumentSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;

	
private:
	std::unique_ptr<Timeline::DocumentView> mDocumentView;
};

}
