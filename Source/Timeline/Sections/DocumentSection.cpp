#include "DocumentSection.h"
#include "Util/Colors.h"
#include "../Views/DocumentView.h"
#include "../ZoomState/ZoomState.h"

using namespace Timeline;

//===============
DocumentSection::DocumentSection(Timeline::ZoomState& zoomState)
: Timeline::ViewportSection(zoomState)
{
	mDocumentView = std::make_unique<DocumentView>();
	mDocumentView->setSize(1000, 1000);
	
	mViewport->setViewedComponent(mDocumentView.get());
	mViewport->setScrollBarsShown(true, true);
	addAndMakeVisible(mViewport.get());
}

//===============
DocumentSection::~DocumentSection()
{
	mViewport.reset();
	mDocumentView.reset();
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



