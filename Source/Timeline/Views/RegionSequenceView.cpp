
#include "RegionSequenceView.h"
#include "PlaybackRegionView.h"

#include "Util/Colors.h"

#include "../Objects/Timeline_RegionSequence.h"
#include "../Objects/Timeline_PlaybackRegion.h"


using namespace Timeline;

RegionSequenceView::RegionSequenceView(Timeline::RegionSequence& sequence, Timeline::ZoomState& zoomState)
: Timeline::ObjectView(zoomState)
, mRegionSequence(sequence)
{
	refresh();
}

RegionSequenceView::~RegionSequenceView()
{
	
}

void RegionSequenceView::paint(juce::Graphics &g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::regionSequenceBkgd));
	g.setColour(Colors::getColor(Colors::ColorID::regionSequenceOutline));
	g.drawRoundedRectangle(getLocalBounds().toFloat(), 2.f, 2.f);
	
}


//===========================
int RegionSequenceView::getEndPositionOfFinalRegion()
{
	int endPosition = 0;
	for(auto regionView : mPlaybackRegionViews)
	{
		int rightEdge = regionView->getRight();
		if(endPosition < rightEdge)
			endPosition = rightEdge;
	}
	return endPosition;
}


//===========================
void RegionSequenceView::_updateSize()
{
	// convert the end of final PlaybackRegion in Timeline samples to Timeline seconds using SampleRate given to ZoomState
	auto endInTimelineSeconds = mRegionSequence.getEndOfFinalRegion() / getZoomState().getSampleRate();
	auto width = (int)(endInTimelineSeconds * getZoomState().getPixelsPerSecond());
	auto height = getZoomState().getSequenceHeight();
	
	this->setSize(width, height);
}

//===========================
void RegionSequenceView::_createChildren()
{
	auto regions = mRegionSequence.getPlaybackRegions();
	for(auto pRegion : regions)
		this->_createPlaybackRegionView(pRegion);
}

//===========================
void RegionSequenceView::_positionChildren()
{
	for(auto regionView : mPlaybackRegionViews)
	{
		const auto& playbackRegion = regionView->getPlaybackRegion();
		
		// Start/End of our pixels
		int startX = (int)playbackRegion.getRangeInTimelineSeconds().getStart() * getZoomState().getPixelsPerSecond();
		regionView->setTopLeftPosition(startX, getZoomState().getRegionPadding());
	}
}


void RegionSequenceView::_createPlaybackRegionView(Timeline::PlaybackRegion* pRegion)
{
	auto regionView = std::make_unique<Timeline::PlaybackRegionView>(*pRegion, getZoomState());
	this->addAndMakeVisible(*regionView.get());
	mPlaybackRegionViews.add(std::move(regionView));
	resized();
}
