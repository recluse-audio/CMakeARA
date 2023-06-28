
#pragma once
#include <Util/Juce_Header.h>
#include "ObjectView.h"
#include "RegionSequenceView.h" // having problems moving this to cpp.  I wonder why?

namespace Timeline
{


class PlaybackRegion;
class RegionSequence;
class Document;

class DocumentView : public juce::Component
, public Timeline::ObjectView
{
public:
	//
	DocumentView(Timeline::Document& document, Timeline::ZoomState& zoomState);
	
	//
	void paint(juce::Graphics& g) override;
	
		
private:
	Timeline::Document& mDocument;
	juce::OwnedArray<Timeline::RegionSequenceView>	mRegionSequences;
	
	// recalculates the size and calls 'setSize()' according to how many RegionSequences and what the longest duration is
	void _updateSize() override;
	
	void _createChildren() override;
	
	void _positionChildren() override;
	
	
	
	// Adds RegionSequenceView for given RegionSequence
	void _addRegionSequence(Timeline::RegionSequence& pSequence);
	
	// clears all views associated with TimelineObjects / Document
	void _addRegionSequences(std::vector<Timeline::RegionSequence*> sequences);
	
	/**
		 Calculates and returns the width of the longest sequence in pixels
		 We could ask the SequenceViews what their length is, but they might not have had their zoomState updated yet
	*/
	int _getLongestSequenceWidth(int pixPerSecond);
};

}
