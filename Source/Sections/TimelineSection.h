#pragma once
#include <Util/Juce_Header.h>

// Forward declaration
namespace Timeline
{
	class TimeRulerSection;
	class SequenceHeadersSection;
	class DocumentSection;
	class ZoomControlsSection;
}

class TimelineSection : public juce::Component
, public juce::ScrollBar::Listener
{
public:
	TimelineSection();
	~TimelineSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	void scrollBarMoved(juce::ScrollBar* scrollBarThatMoved, double newRangeStart) override;
	
private:
	std::unique_ptr<Timeline::TimeRulerSection> 		mTimeRulerSection;
	std::unique_ptr<Timeline::SequenceHeadersSection> 	mSequenceHeadersSection;
	std::unique_ptr<Timeline::DocumentSection>			mDocumentSection;
	std::unique_ptr<Timeline::ZoomControlsSection> 		mZoomControlsSection;
	


	
	
	
};


