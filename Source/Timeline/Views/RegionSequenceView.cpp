
#include "RegionSequenceView.h"
#include "PlaybackRegionView.h"
#include "Util/Colors.h"

using namespace Timeline;

RegionSequenceView::RegionSequenceView()
{

	
	setSize(100,100);
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


void RegionSequenceView::addPlaybackRegionView(Timeline::PlaybackRegionView *pView)
{
	
}
