#include "TrackHeadersSection.h"
#include "Util/Colors.h"

TrackHeadersSection::TrackHeadersSection()
{
	
}

TrackHeadersSection::~TrackHeadersSection()
{
	
}

void TrackHeadersSection::paint(juce::Graphics& g)
{
	g.fillAll(Colors::getColor(Colors::ColorID::emptySectionBkgd));
	
	g.setColour(Colors::getColor(Colors::ColorID::emptySectionOutline));
	g.drawRect(this->getLocalBounds());
}

void TrackHeadersSection::resized()
{
	
}
