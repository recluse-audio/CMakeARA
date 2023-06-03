
#pragma once
#include <Util/Juce_Header.h>

namespace Timeline
{


class RegionSequenceView;

class DocumentView : public juce::Component
{
public:
	DocumentView();
	~DocumentView();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
private:
	std::unique_ptr<RegionSequenceView> mRegionSequenceView;
};

}
