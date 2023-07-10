#include <catch2/catch_test_macros.hpp>

#include "Util/Juce_Header.h"
#include "Test_Utils/TestUtils.h"
#include "Test_Utils/DocumentFactory.h"

#include "Sections/TimelineSection.h"
#include "Timeline/ZoomState/ZoomState.h"
#include "Timeline/ZoomState/ZoomStateListener.h"

#include "Timeline/Sections/ViewportSection.h"

#include "Timeline/Views/PlaybackRegionView.h"
#include "Timeline/Views/RegionSequenceView.h"
#include "Timeline/Views/DocumentView.h"

#include "Timeline/Objects/Timeline_Object.h"
#include "Timeline/Objects/Timeline_PlaybackRegion.h"
#include "Timeline/Objects/Timeline_RegionSequence.h"
#include "Timeline/Objects/Timeline_Document.h"

#include "../Source/Test_Timeline/Test_RegionSequence.h"
#include "../Source/Test_Timeline/Test_PlaybackRegion.h"



/**
	A main locus of focus should be to verify instantiation of all the Timeline::Views for each Timeline::Object
	
	However the abstractive Timeline::Document instance is populated, be it by test or ARA or some other subclass, 
 
*/
class ViewTester
{
public:
	ViewTester()
	{
		
	}
	~ViewTester(){}

	// refers to child components of the docView
	int getNumSequenceChildren(Timeline::DocumentView& docView)
	{
		int sequenceChildren = 0;
		
		for(int i = 0; i < docView.getNumChildComponents(); ++i)
		{
			juce::Component* child = docView.getChildComponent(i);
			if(dynamic_cast<Timeline::RegionSequenceView*>(child) != nullptr)
			{
				sequenceChildren++;
			}
		}
		
		return sequenceChildren;
	}
	
	int getNumZoomStateListeners(Timeline::DocumentView& docView)
	{
		return (int)getZoomStateListeners(docView).size();
	}
	
	//
	juce::Array<juce::Component*> getZoomStateListeners (Timeline::DocumentView& docView)
	{
		juce::Array<juce::Component*> zoomStateListeners;
		
		for(int i = 0; i < docView.getNumChildComponents(); i++)
		{
			juce::Component* childComponent = docView.getChildComponent(i);
			if(dynamic_cast<Timeline::ZoomStateListener*>(childComponent) != nullptr)
			{
				zoomStateListeners.add(childComponent);
			}
		}
		
		return zoomStateListeners;
	}
	

	//
	juce::Array<juce::Component*> getZoomStateListeners (Timeline::TimelineSection& timelineSection)
	{
		juce::Array<juce::Component*> zoomStateListeners;
		
		for(int i = 0; i < timelineSection.getNumChildComponents(); i++)
		{
			juce::Component* childComponent = timelineSection.getChildComponent(i);
			if(dynamic_cast<Timeline::ZoomStateListener*>(childComponent) != nullptr)
			{
				zoomStateListeners.add(childComponent);
			}
		}
		
		return zoomStateListeners;
	}
	
	void addRegionSequence(Timeline::RegionSequence* newSequence)
	{

	}

private:
};


//==========================
TEST_CASE("Testing DocumentFactory")
{
	TestUtils::SetupAndTeardown setupAndTeardown;

	DocumentFactory docFactory;
	auto document = docFactory.createDocument(3, 4);
	
	auto sequences = document->getRegionSequences();
	REQUIRE(sequences.size() == 3);
	for(auto sequence : sequences)
	{
		auto regions = sequence->getPlaybackRegions();
		REQUIRE(regions.size() == 4);
	}


}





//==========================
TEST_CASE("DocumentView builds from a Timeline::Document correctly")
{
	TestUtils::SetupAndTeardown setupAndTeardown;

	// Helper class for checking our views got added, not just juce::components
	ViewTester viewTester;
	
	// Make Document
	DocumentFactory docFactory;
	int numSequences = 3;
	int numRegionsPerSequence = 4;
	auto document = docFactory.createDocument(numSequences, numRegionsPerSequence);
	
	// Make View
	Timeline::ZoomState zoomState;
	auto docView = std::make_unique<Timeline::DocumentView>(*document.get(), zoomState);


	
	CHECK(viewTester.getNumSequenceChildren(*docView) == numSequences); // TODO: pass 3 by variable

}


//



/** Might not be necessary if we don't use Timeline::Document to pass all the info to the DocumentView */
TEST_CASE("Can make juce::var")
{

	// auto trackName = juce::String("Track 1");
	// int regionNumber = 1;
	
	// juce::DynamicObject::Ptr sequenceObject = new juce::DynamicObject();
	// sequenceObject->setProperty("Track Name", trackName);

	// juce::DynamicObject::Ptr regionObject = new juce::DynamicObject();
	// regionObject->setProperty("Region Number", regionNumber);
	
	// // Try adding regionObject as property of sequenceObject
	// sequenceObject->setProperty("PlaybackRegion", juce::var(regionObject.get()));
	
	// juce::var sequenceVar = juce::var(sequenceObject.get());
	
	// REQUIRE(sequenceVar["Track Name"] == trackName);
	// REQUIRE(sequenceVar.hasProperty("PlaybackRegion"));
	// REQUIRE(sequenceVar["PlaybackRegion"] == juce::var(regionObject.get()));
	
	// auto regionVar = sequenceVar["PlaybackRegion"];
	// REQUIRE(regionVar.hasProperty("Region Number"));
	//regionSequence = nullptr;
}


