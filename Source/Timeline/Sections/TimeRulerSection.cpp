#include "TimeRulerSection.h"
#include "Util/Colors.h"

TimeRulerSection::TimeRulerSection()
{
	
}

TimeRulerSection::~TimeRulerSection()
{
	
}

void TimeRulerSection::paint(juce::Graphics& g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::emptySectionBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::emptySectionOutline));
	g.drawRect(this->getLocalBounds());
}

void TimeRulerSection::resized()
{
	
}
