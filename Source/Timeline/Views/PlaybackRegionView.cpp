
#include "PlaybackRegionView.h"
#include "Util/Colors.h"

using namespace Timeline;

PlaybackRegionView::PlaybackRegionView()
{
	setSize(100,100);
}

PlaybackRegionView::~PlaybackRegionView()
{
	
}

//=================
void PlaybackRegionView::paint(juce::Graphics &g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::playbackRegionBkgd));
	g.setColour(Colors::getColor(Colors::ColorID::playbackRegionOutline));
	g.drawRoundedRectangle(getLocalBounds().toFloat(), 2.f, 2.f);
	
}

//=================
void PlaybackRegionView::resized()
{

}

//==================
void PlaybackRegionView::updateZoomState(ZoomState *zoomState)
{
	auto regionHeight = zoomState->getSequenceHeight() - 2;
	auto pixPerSecond = zoomState->getPixelsPerSecond();
}
