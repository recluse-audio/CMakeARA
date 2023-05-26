#pragma once
#include <Util/Juce_Header.h>

class TimeRulerSection;
class SequenceHeadersSection;
class DocumentSection;
class ZoomControlsSection;

class TimelineSection : public juce::Component
{
public:
	TimelineSection();
	~TimelineSection();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
private:
	std::unique_ptr<TimeRulerSection> 			mTimeRulerSection;
	std::unique_ptr<SequenceHeadersSection> 	mSequenceHeadersSection;
	std::unique_ptr<DocumentSection>			mDocumentSection;
	std::unique_ptr<ZoomControlsSection> 		mZoomControlsSection;
	
	
};


