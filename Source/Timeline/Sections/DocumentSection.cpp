#include "DocumentSection.h"
#include "Util/Colors.h"
#include "../Views/DocumentView.h"
#include "../ZoomState/ZoomState.h"


using namespace Timeline;

//===============
DocumentSection::DocumentSection(Timeline::ZoomState& zoomState)
: Timeline::ViewportSection(zoomState)
{
	mViewport->setScrollBarsShown(true, true);
	addAndMakeVisible(mViewport.get());
}

//===============
DocumentSection::~DocumentSection()
{

}

//===============
void DocumentSection::paint(juce::Graphics& g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::emptySectionBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::emptySectionOutline));
	g.drawRect(this->getLocalBounds());
}

//===============
void DocumentSection::resized()
{
	auto bounds = this->getLocalBounds();
	mViewport->setBounds(bounds);
}


void DocumentSection::loadDocument(Timeline::Document &document)
{
	mDocumentView.reset();
	mDocumentView = std::make_unique<Timeline::DocumentView>(document, mZoomState);
	mViewport->setViewedComponent(mDocumentView.get());
}
