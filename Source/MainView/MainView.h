#pragma once
#include <Util/Juce_Header.h>

class NavigationSection;
class TimelineSection;
class InspectSection;

class MainView : public juce::Component
{
public:
	MainView();
	~MainView();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	
private:
	std::unique_ptr<NavigationSection> 	mNavigationSection;
	std::unique_ptr<TimelineSection> 	mTimelineSection;
	std::unique_ptr<InspectSection> 	mInspectSection;
	
};
