#include "TracksSection.h"
#include "Util/Colors.h"

TracksSection::TracksSection()
{
	
}

TracksSection::~TracksSection()
{
	
}

void TracksSection::paint(juce::Graphics& g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::emptySectionBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::emptySectionOutline));
	g.drawRect(this->getLocalBounds());
}

void TracksSection::resized()
{
	
}

