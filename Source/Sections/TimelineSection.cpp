#include "TimelineSection.h"
#include "Util/Colors.h"
#include "Timeline/Sections/TimeRulerSection.h"
#include "Timeline/Sections/SequenceHeadersSection.h"
#include "Timeline/Sections/DocumentSection.h"
#include "Timeline/Sections/ZoomControlsSection.h"

#include "../Test_Timeline/Test_RegionSequence.h"
#include "Timeline/Views/DocumentView.h"

#include "Timeline/ZoomState/ZoomState.h"


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
	
	mZoomControlsSection = std::make_unique<Timeline::ZoomControlsSection>();
	addAndMakeVisible(mZoomControlsSection.get());
	
	mDocumentSection->getViewport()->getHorizontalScrollBar().addListener(this);
	mDocumentSection->getViewport()->getVerticalScrollBar().addListener(this);
	
	mTestButton =  std::make_unique<juce::TextButton>("TEST BUTTON");
	mTestButton->addListener(this);
	mTestButton->setAlwaysOnTop(true);
	addAndMakeVisible(mTestButton.get());
	
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
	mTestButton->setBounds(100, 200, 100, 25);
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

//===============
void TimelineSection::buttonClicked(juce::Button *b)
{
	if(b == mTestButton.get())
	{
		auto documentView = dynamic_cast<Timeline::DocumentView*>(mDocumentSection->getViewport()->getViewedComponent());
		
		// Make up some
		auto regionSequence = std::make_unique<Test::RegionSequence>();
		regionSequence->addRegionAtRange(0, 1000);
		regionSequence->addRegionAtRange(1200, 15000);
		regionSequence->addRegionAtRange(19000, 200000);
		
		documentView->addRegionSequence(*regionSequence.get());
		
	}
}



