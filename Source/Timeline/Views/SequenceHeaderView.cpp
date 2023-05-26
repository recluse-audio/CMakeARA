#include "SequenceHeaderView.h"
#include "Util/Colors.h"

SequenceHeaderView::SequenceHeaderView()
{
	
}

SequenceHeaderView::~SequenceHeaderView()
{
	
}

void SequenceHeaderView::paint(juce::Graphics &g)
{
	g.fillAll(juce::Colours::pink);
	
	g.setColour(juce::Colours::transparentBlack.withAlpha(0.2f));
	
	// draw horizontal lines
	int yPos = 0;
	while( yPos < this->getHeight() )
	{
		g.drawHorizontalLine(yPos, 0, this->getWidth());
		yPos+=80;
	}
}

void SequenceHeaderView::resized()
{
	
}
