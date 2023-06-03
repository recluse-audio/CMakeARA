#include "TimeRulerView.h"
#include "Util/Colors.h"


using namespace Timeline;

TimeRulerView::TimeRulerView()
{
	
}

TimeRulerView::~TimeRulerView()
{
	
}

void TimeRulerView::paint(juce::Graphics &g)
{
	g.fillAll(juce::Colours::pink);
	
	g.setColour(juce::Colours::black);
	int i = 0;
	while( i < this->getWidth() )
	{
		g.drawVerticalLine(i, 0, 30);
		i+=20;
	}
}

void TimeRulerView::resized()
{
	
}
