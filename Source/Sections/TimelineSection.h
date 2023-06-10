#pragma once
#include <Util/Juce_Header.h>

// Forward declaration
namespace Timeline
{
	class TimeRulerSection;
	class SequenceHeadersSection;
	class DocumentSection;
	class ZoomControlsSection;
	class ZoomState;

}

class TimelineSection : public juce::Component
, public juce::ScrollBar::Listener
, public juce::Button::Listener
{
public:
	TimelineSection();
	~TimelineSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
	void scrollBarMoved(juce::ScrollBar* scrollBarThatMoved, double newRangeStart) override;
	void buttonClicked(juce::Button* b) override;
	
	/**
		CONTRACTED FUNCTIONS:
		I promise that these functions will resize the child components that are ZoomStateListeners correctly according to the current ZoomState.
		I promise these functions will update mZoomState (which promises to convert to pixPerSecond etc.)
	 */
	void setHorizontalZoomFactor(double zoomFactor);
	void setVerticalZoomFactor(double zoomFactor);
private:
	std::unique_ptr<Timeline::ZoomState>				mZoomState;
	
	std::unique_ptr<Timeline::TimeRulerSection> 		mTimeRulerSection;
	std::unique_ptr<Timeline::SequenceHeadersSection> 	mSequenceHeadersSection;
	std::unique_ptr<Timeline::DocumentSection>			mDocumentSection;
	std::unique_ptr<Timeline::ZoomControlsSection> 		mZoomControlsSection;
	

	std::unique_ptr<juce::TextButton> mTestButton;
	
	
	
};


