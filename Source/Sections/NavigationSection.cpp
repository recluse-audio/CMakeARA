#include "NavigationSection.h"
#include "Util/Colors.h"

NavigationSection::NavigationSection()
{

}

NavigationSection::~NavigationSection()
{
	
}

void NavigationSection::paint(juce::Graphics &g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::navigationBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::navigationOutline));
	g.drawRoundedRectangle(this->getLocalBounds().toFloat(), 2.f, 2.f);
}

void NavigationSection::resized()
{
	
}

