#include "ZoomControlsSection.h"
#include "Util/Colors.h"

ZoomControlsSection::ZoomControlsSection()
{
	
}

ZoomControlsSection::~ZoomControlsSection()
{
	
}

void ZoomControlsSection::paint(juce::Graphics& g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::emptySectionBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::emptySectionOutline));
	g.drawRect(this->getLocalBounds());
}

void ZoomControlsSection::resized()
{
	
}


