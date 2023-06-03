
#include "RegionSequenceView.h"
#include "PlaybackRegionView.h"
#include "Util/Colors.h"

using namespace Timeline;

RegionSequenceView::RegionSequenceView()
{
	mPlaybackRegionView = std::make_unique<PlaybackRegionView>();
	addAndMakeVisible(mPlaybackRegionView.get());
	
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
	auto bounds = this->getLocalBounds();
	
	auto regionPixelBuffer = 1; 	// Make playback region fit within region sequence
	auto regionHeight = bounds.getHeight() - (regionPixelBuffer * 2);
	
	mPlaybackRegionView->setBounds(0, regionPixelBuffer, 100, regionHeight);
}

