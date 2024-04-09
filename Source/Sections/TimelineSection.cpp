#include "TimelineSection.h"
#include "Util/Colors.h"
#include "Timeline/Sections/TimeRulerSection.h"
#include "Timeline/Sections/SequenceHeadersSection.h"
#include "Timeline/Sections/DocumentSection.h"
#include "Timeline/Sections/ZoomControlsSection.h"

#include "Timeline/Objects/Timeline_Document.h"
#include "Timeline/Views/DocumentView.h"

#include "Timeline/ZoomState/ZoomState.h"

using namespace Timeline;

//==============
TimelineSection::TimelineSection()
{
	mZoomState = std::make_unique<Timeline::ZoomState>();
	
	mTimeRulerSection = std::make_unique<Timeline::TimeRulerSection>(*mZoomState.get());
	addAndMakeVisible(mTimeRulerSection.get());
	
	mSequenceHeadersSection = std::make_unique<Timeline::SequenceHeadersSection>(*mZoomState.get());
	addAndMakeVisible(mSequenceHeadersSection.get());
	
	mDocumentSection = std::make_unique<Timeline::DocumentSection>(*mZoomState.get());
	addAndMakeVisible(mDocumentSection.get());
	
	mZoomControlsSection = std::make_unique<Timeline::ZoomControlsSection>(*mZoomState.get());
	addAndMakeVisible(mZoomControlsSection.get());
	
	mDocumentSection->getViewport()->getHorizontalScrollBar().addListener(this);
	mDocumentSection->getViewport()->getVerticalScrollBar().addListener(this);
	

	
	setSize(700, 270);
}


//==============
TimelineSection::~TimelineSection()
{
	mDocumentSection->getViewport()->getHorizontalScrollBar().removeListener(this);
	mDocumentSection->getViewport()->getVerticalScrollBar().removeListener(this);
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
	mZoomControlsSection->setBounds(550, 220, 100, 40);
}

//===============
void TimelineSection::scrollBarMoved(juce::ScrollBar *scrollBar, double newRangeStart)
{
	(void) newRangeStart; // hide warning of unused variable (don't need it here)
	
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


//=================
void TimelineSection::loadDocument(Timeline::Document &document)
{
	mZoomState->setSampleRate(document.getPlaybackSampleRate());
	mDocumentSection->loadDocument(document);
	mZoomState->sendChangeMessage();
	// mSequenceHeadersSection->loadDocument(document);
}
