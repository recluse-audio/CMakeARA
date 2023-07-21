
#include "PlaybackRegionView.h"
#include "Util/Colors.h"
#include "../Objects/Timeline_PlaybackRegion.h"

using namespace Timeline;

PlaybackRegionView::PlaybackRegionView(Timeline::PlaybackRegion& pRegion, Timeline::ZoomState& zoomState)
: Timeline::ObjectView(zoomState)
, mPlaybackRegion(pRegion)
{
	refresh();

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



//==================
void PlaybackRegionView::_updateSize()
{

	auto lengthInSeconds = mPlaybackRegion.getRangeInTimeline().getLength() / getZoomState().getSampleRate();
	int regionWidth = (int)(lengthInSeconds * getZoomState().getPixelsPerSecond());
	int regionHeight = getZoomState().getSequenceHeight() - (getZoomState().getRegionPadding() * 2);
	this->setSize(regionWidth, regionHeight);
	
}

//====================
void PlaybackRegionView::_createChildren()
{
	
}

//====================
void PlaybackRegionView::_positionChildren()
{
	
}

//==================
const Timeline::PlaybackRegion& PlaybackRegionView::getPlaybackRegion() const
{
	return mPlaybackRegion;
}
