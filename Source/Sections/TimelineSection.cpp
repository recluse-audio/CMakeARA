#include "TimelineSection.h"
#include "Util/Colors.h"
#include "Timeline/Sections/TimeRulerSection.h"
#include "Timeline/Sections/SequenceHeadersSection.h"
#include "Timeline/Sections/DocumentSection.h"
#include "Timeline/Sections/ZoomControlsSection.h"


//==============
TimelineSection::TimelineSection()
{
	mTimeRulerSection = std::make_unique<Timeline::TimeRulerSection>();
	addAndMakeVisible(mTimeRulerSection.get());
	
	mSequenceHeadersSection = std::make_unique<Timeline::SequenceHeadersSection>();
	addAndMakeVisible(mSequenceHeadersSection.get());
	
	mDocumentSection = std::make_unique<Timeline::DocumentSection>();
	addAndMakeVisible(mDocumentSection.get());
	
	mZoomControlsSection = std::make_unique<Timeline::ZoomControlsSection>();
	addAndMakeVisible(mZoomControlsSection.get());
	
	mDocumentSection->getViewport()->getHorizontalScrollBar().addListener(this);
	mDocumentSection->getViewport()->getVerticalScrollBar().addListener(this);
	
	setSize(700, 270);
}


//==============
TimelineSection::~TimelineSection()
{
	mTimeRulerSection.reset();
	mSequenceHeadersSection.reset();
	mDocumentSection.reset();
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
	mSequenceHeadersSection->setBounds(0, 30, 100, 270);
	mDocumentSection->setBounds(100, 30, 600, 270);
}

//===============
void TimelineSection::scrollBarMoved(juce::ScrollBar *scrollBar, double newRangeStart)
{
	auto horizontalScrollBar = &mDocumentSection->getViewport()->getHorizontalScrollBar();
	auto verticalScrollBar = &mDocumentSection->getViewport()->getVerticalScrollBar();
	
	if( scrollBar == horizontalScrollBar || scrollBar == verticalScrollBar)
	{
		auto viewPosX = mDocumentSection->getViewport()->getViewPositionX();
		auto viewPosY = mDocumentSection->getViewport()->getViewPositionY();
		mTimeRulerSection->setViewPosition(viewPosX, 0);
		mSequenceHeadersSection->setViewPosition(0, viewPosY);
	}
}
