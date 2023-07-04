#include "ZoomControlsSection.h"
#include "Timeline/widgets/ZoomControls.h"
#include "Util/Colors.h"


using namespace Timeline;

ZoomControlsSection::ZoomControlsSection(Timeline::ZoomState& zoomState) : mZoomState(zoomState)
{
	mZoomOutButton = std::make_unique<juce::TextButton>("Zoom Out");
	mZoomOutButton->setButtonText("-");
	mZoomOutButton->addListener(this);
	addAndMakeVisible(*mZoomOutButton.get());

	mZoomInButton = std::make_unique<juce::TextButton>("Zoom In");
	mZoomInButton->setButtonText("+");
	mZoomInButton->addListener(this);
	addAndMakeVisible(*mZoomInButton.get());

	this->setSize(100, 40);
	mZoomOutButton->setBounds(10, 5, 30, 30);
	mZoomInButton->setBounds(60, 5, 30, 30);

}

ZoomControlsSection::~ZoomControlsSection()
{
	mZoomInButton->removeListener(this);
    mZoomOutButton->removeListener(this);
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


void ZoomControlsSection::buttonClicked(juce::Button* b) 
{
	if(b == mZoomOutButton.get())
		mZoomState.zoomOut();
	if(b == mZoomInButton.get())
		mZoomState.zoomIn();
}