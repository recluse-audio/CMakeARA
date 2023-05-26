#include "SequenceHeadersSection.h"
#include "Util/Colors.h"
#include "../Views/SequenceHeaderView.h"

SequenceHeadersSection::SequenceHeadersSection()
{
	mSequenceHeaderView = std::make_unique<SequenceHeaderView>();
	mSequenceHeaderView->setSize(100, 1000);
	mViewport = std::make_unique<juce::Viewport>();
	mViewport->setViewedComponent(mSequenceHeaderView.get());
	mViewport->setScrollBarsShown(true, false);
	addAndMakeVisible(mViewport.get());
}

SequenceHeadersSection::~SequenceHeadersSection()
{
	mViewport.reset();
	mSequenceHeaderView.reset();
}

void SequenceHeadersSection::paint(juce::Graphics& g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::emptySectionBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::emptySectionOutline));
	g.drawRect(this->getLocalBounds());
}

void SequenceHeadersSection::resized()
{
	auto bounds = this->getLocalBounds();
	mViewport->setBounds(bounds);
}
