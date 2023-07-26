#pragma once
#include<Util/Juce_Header.h>

class NavigationSection;
class InspectSection;
namespace Timeline
{
	class TimelineSection;
}

class MainView : public juce::Component
{
public:
	MainView();
	~MainView() override;
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	
private:
	std::unique_ptr<NavigationSection> 	mNavigationSection;
	std::unique_ptr<Timeline::TimelineSection> 	mTimelineSection;
	std::unique_ptr<InspectSection> 	mInspectSection;
	
};
