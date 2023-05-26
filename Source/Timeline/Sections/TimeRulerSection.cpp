#include "TimeRulerSection.h"
#include "Util/Colors.h"
#include "../Views/TimeRulerView.h"

TimeRulerSection::TimeRulerSection()
{
	mTimeRuler = std::make_unique<TimeRulerView>();
	mTimeRuler->setSize(1000, 30);
	mViewport = std::make_unique<juce::Viewport>();
	mViewport->setViewedComponent(mTimeRuler.get());
	mViewport->setScrollBarsShown(false, true);
	addAndMakeVisible(mViewport.get());
}

TimeRulerSection::~TimeRulerSection()
{
	mViewport.reset();
	mTimeRuler.reset();
}

void TimeRulerSection::paint(juce::Graphics& g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::emptySectionBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::emptySectionOutline));
	g.drawRect(this->getLocalBounds());
}

void TimeRulerSection::resized()
{
	auto bounds = this->getLocalBounds();
	mViewport->setBounds(bounds);
}
