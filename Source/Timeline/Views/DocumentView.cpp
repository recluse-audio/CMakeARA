#include "DocumentView.h"
#include "Util/Colors.h"
#include "RegionSequenceView.h"

using namespace Timeline;

DocumentView::DocumentView()
{
	mRegionSequenceView = std::make_unique<RegionSequenceView>();
	addAndMakeVisible(mRegionSequenceView.get());
	
	setSize(1000, 1000);
}

DocumentView::~DocumentView()
{
	mRegionSequenceView.reset();
}

void DocumentView::paint(juce::Graphics &g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::timelineBkgd));
	
	g.setColour(juce::Colours::transparentBlack.withAlpha(0.2f));
	
	// draw vertical lines
	int xPos = 0;
	while( xPos < this->getWidth() )
	{
		g.drawVerticalLine(xPos, 0, this->getHeight());
		xPos+=20;
	}
	
	// draw horizontal lines
	int yPos = 0;
	while( yPos < this->getHeight() )
	{
		g.drawHorizontalLine(yPos, 0, this->getWidth());
		yPos+=80;
	}
}

void DocumentView::resized()
{
	auto bounds = getLocalBounds();
	mRegionSequenceView->setBounds(0, 0, bounds.getWidth(), 80);
}
