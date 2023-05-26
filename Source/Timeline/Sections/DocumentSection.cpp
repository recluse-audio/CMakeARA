#include "DocumentSection.h"
#include "Util/Colors.h"
#include "../Views/DocumentView.h"

DocumentSection::DocumentSection()
{
	mDocumentView = std::make_unique<DocumentView>();
	mDocumentView->setSize(1000, 1000);
	mViewport = std::make_unique<juce::Viewport>();
	mViewport->setViewedComponent(mDocumentView.get());
	mViewport->setScrollBarsShown(true, true);
	addAndMakeVisible(mViewport.get());
}

DocumentSection::~DocumentSection()
{
	mViewport.reset();
	mDocumentView.reset();
}

void DocumentSection::paint(juce::Graphics& g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::emptySectionBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::emptySectionOutline));
	g.drawRect(this->getLocalBounds());
}

void DocumentSection::resized()
{
	auto bounds = this->getLocalBounds();
	mViewport->setBounds(bounds);
}

