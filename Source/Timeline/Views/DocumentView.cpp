#include "DocumentView.h"
#include "RegionSequenceView.h"
#include "PlaybackRegionView.h"

#include "../Objects/Timeline_PlaybackRegion.h"
#include "../Objects/Timeline_RegionSequence.h"
//#include "../../../Tests/test_DocumentController.cpp"

#include "Util/Colors.h"

using namespace Timeline;

DocumentView::DocumentView()
{

	
	setSize(1000, 1000);
}

DocumentView::~DocumentView()
{
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
	auto sequenceHeight = 100;
	for(int i = 0; i < mRegionSequences.size(); i++)
	{
		mRegionSequences[i]->setTopLeftPosition(0, i * sequenceHeight);
	}
}

//===========================
void DocumentView::addRegionSequence(Timeline::RegionSequence& pSequence)
{
	auto sequenceView = std::make_unique<Timeline::RegionSequenceView>(pSequence);
	this->addAndMakeVisible(*sequenceView.get());
	mRegionSequences.add(std::move(sequenceView));
	resized();
}


//============================
void DocumentView::addRegionSequences(std::vector<Timeline::RegionSequence*> sequences)
{
	for(auto regionSequence : sequences)
	{
		addRegionSequence(*regionSequence);
	}
}


//=============================
void DocumentView::resetTimeline()
{
	mRegionSequences.clear();
}
 


//===============================
void DocumentView::updateZoomState(Timeline::ZoomState* zoomState)
{
	
}

