#include "InspectSection.h"
#include "Util/Colors.h"

InspectSection::InspectSection()
{

}

InspectSection::~InspectSection()
{
	
}

void InspectSection::paint(juce::Graphics &g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::inspectBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::inspectOutline));
	g.drawRoundedRectangle(this->getLocalBounds().toFloat(), 2.f, 2.f);
}

void InspectSection::resized()
{
	
}


