
#pragma once
#include <Util/Juce_Header.h>


class DocumentView : public juce::Component
{
public:
	DocumentView();
	~DocumentView();
	
	void paint(juce::Graphics& g) override;
	void resized() override;
	
private:

};
