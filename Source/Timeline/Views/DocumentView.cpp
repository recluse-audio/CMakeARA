#include "DocumentView.h"
#include "RegionSequenceView.h"
#include "PlaybackRegionView.h"

#include "../Objects/Timeline_PlaybackRegion.h"
#include "../Objects/Timeline_RegionSequence.h"
#include "../Objects/Timeline_Document.h"
//#include "../../../Tests/test_DocumentController.cpp"

#include "Util/Colors.h"

using namespace Timeline;

DocumentView::DocumentView(Timeline::Document& document, Timeline::ZoomState& zoomState)
: mDocument(document)
, Timeline::ObjectView(zoomState)
{
	refresh();
}



//==================================
void DocumentView::paint(juce::Graphics &g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::timelineBkgd));
	
	g.setColour(juce::Colours::transparentBlack.withAlpha(0.2f));
	
	// draw vertical lines
	int xPos = 0;
	while( xPos < this->getWidth() )
	{
		g.drawVerticalLine(xPos, 0, this->getHeight());
		xPos += getZoomState().getPixelsPerSecond();
	}
	

}


//=================================
void DocumentView::_updateSize()
{
	int numSequences = mDocument.getNumSequences();
	int extraSequenceSpace = 3; // equivalent to 3 extra sequences
	auto height = getZoomState().getSequenceHeight() * (numSequences + extraSequenceSpace);
	
	auto width = _getLongestSequenceWidth(getZoomState().getPixelsPerSecond());
	
	this->setSize(width, height);
}


//=================================
void DocumentView::_createChildren()
{
	auto sequences = mDocument.getRegionSequences();
	_addRegionSequences(sequences);
}


//=================================
void DocumentView::_positionChildren()
{
	for(int i = 0; i < mRegionSequences.size(); i++)
	{
		int yPos = getZoomState().getSequenceHeight() * i;
		mRegionSequences[i]->setTopLeftPosition(0, yPos);
	}
}


//================================
int DocumentView::_getLongestSequenceWidth(int pixPerSecond)
{
	int longestWidth = (int)mDocument.getTimelineLength() * pixPerSecond;
	return longestWidth;
}


//===========================
void DocumentView::_addRegionSequence(Timeline::RegionSequence& pSequence)
{
	auto sequenceView = std::make_unique<Timeline::RegionSequenceView>(pSequence, getZoomState());
	this->addAndMakeVisible(*sequenceView.get());
	mRegionSequences.add(std::move(sequenceView));
}


//============================
void DocumentView::_addRegionSequences(std::vector<Timeline::RegionSequence*> sequences)
{
	for(auto regionSequence : sequences)
	{
		_addRegionSequence(*regionSequence);
	}
}
