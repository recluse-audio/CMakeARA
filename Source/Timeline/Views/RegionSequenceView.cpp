
#include "RegionSequenceView.h"
#include "PlaybackRegionView.h"

#include "Util/Colors.h"

#include "../Objects/Timeline_RegionSequence.h"
#include "../Objects/Timeline_PlaybackRegion.h"


using namespace Timeline;

RegionSequenceView::RegionSequenceView(Timeline::RegionSequence& sequence) : mRegionSequence(sequence)
{
	
	setSize(1000,100);
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

void RegionSequenceView::resized()
{

	
}




void RegionSequenceView::updateZoomState(Timeline::ZoomState *zoomState)
{
	
}

void RegionSequenceView::setZoomStateToFollow(Timeline::ZoomState *zoomState)
{
	zoomState->addChangeListener(this);

}

void RegionSequenceView::createPlaybackRegionView(Timeline::PlaybackRegion* pRegion)
{
	auto regionView = std::make_unique<Timeline::PlaybackRegionView>(*pRegion);
	this->addAndMakeVisible(*regionView.get());
	mPlaybackRegionViews.add(std::move(regionView));
	resized();
}
