

#include <Util/Juce_Header.h>
/**
	Draws a region with a start/end time and a thumbnail
	Uses a range because juce catches funny business for us
 */
class TimelineRegion : public juce::Component
{
public:
	TimelineRegion(juce::Range<double> timeRange)
	{
		regionTimeRange = timeRange;
	}
	

	
	void paint(juce::Graphics& g) override
	{
		g.setColour(juce::Colours::yellow);
		g.fillAll();
	}
	
	void resized() override
	{
		
	}
	
	double getStartTime() const
	{
		return regionTimeRange.getStart();
	}
	
	double getDuration() const
	{
		return regionTimeRange.getLength();
	}
	
	
	

	
private:
	juce::Range<double> regionTimeRange;
	
	
};
