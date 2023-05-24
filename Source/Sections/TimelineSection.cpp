#include "TimelineSection.h"
#include "Util/Colors.h"
#include "Timeline/Sections/TimeRulerSection.h"
#include "Timeline/Sections/TrackHeadersSection.h"
#include "Timeline/Sections/TracksSection.h"
#include "Timeline/Sections/ZoomControlsSection.h"

//==============
TimelineSection::TimelineSection()
{
	mTimeRulerSection = std::make_unique<TimeRulerSection>();
	addAndMakeVisible(mTimeRulerSection.get());
	
	mTrackHeadersSection = std::make_unique<TrackHeadersSection>();
	addAndMakeVisible(mTrackHeadersSection.get());
	
	mTracksSection = std::make_unique<TracksSection>();
	addAndMakeVisible(mTracksSection.get());
	
	mZoomControlsSection = std::make_unique<ZoomControlsSection>();
	addAndMakeVisible(mZoomControlsSection.get());
	
	setSize(700, 270);
}


//==============
TimelineSection::~TimelineSection()
{
	mTimeRulerSection.reset();
	mTrackHeadersSection.reset();
	mTracksSection.reset();
	mZoomControlsSection.reset();
}


//==============
void TimelineSection::paint(juce::Graphics &g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::timelineBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::timelineOutline));
	g.drawRoundedRectangle(this->getLocalBounds().toFloat(), 2.f, 2.f);
}


//==============
void TimelineSection::resized()
{
	mTimeRulerSection->setBounds(100, 0, 600, 30);
	mTrackHeadersSection->setBounds(0, 30, 100, 270);
	mTracksSection->setBounds(100, 30, 600, 270);
}

