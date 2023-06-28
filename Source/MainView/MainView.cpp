#include "MainView.h"
#include "Util/Colors.h"
#include "Sections/NavigationSection.h"
#include "Sections/TimelineSection.h"
#include "Sections/InspectSection.h"


//===================
MainView::MainView()
{
	mNavigationSection = std::make_unique<NavigationSection>();
	addAndMakeVisible(mNavigationSection.get());
	
	mInspectSection = std::make_unique<InspectSection>();
	addAndMakeVisible(mInspectSection.get());
	
	mTimelineSection = std::make_unique<Timeline::TimelineSection>();
	mTimelineSection->setComponentID("TimelineSection"); // TODO: Do this in the TimelineSection constructor?
	addAndMakeVisible(mTimelineSection.get());

}


//===================
MainView::~MainView()
{
	mNavigationSection.reset();
	mTimelineSection.reset();
	mInspectSection.reset();
}


//===================
void MainView::paint(juce::Graphics &g)
{
	//g.fillAll(Colors::getColor(Colors::ColorID::emptySectionBkgd));
	g.fillAll(juce::Colours::red);
}


//===================
void MainView::resized()
{
	mNavigationSection->setBounds(0, 0, 100, 300);
	mInspectSection->setBounds(100, 270, 700, 30);
	mTimelineSection->setBounds(100, 0, 700, 270);

}

