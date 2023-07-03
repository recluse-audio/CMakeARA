// #include <catch2/catch_test_macros.hpp>

// #include "Util/Juce_Header.h"
// #include "Test_Utils/TestUtils.h"

// #include "Sections/TimelineSection.h"
// #include "Timeline/ZoomState/ZoomState.h"
// #include "Timeline/ZoomState/ZoomStateListener.h"

// #include "Timeline/Sections/ViewportSection.h"

// #include "Timeline/Views/PlaybackRegionView.h"
// #include "Timeline/Views/RegionSequenceView.h"
// #include "Timeline/Views/DocumentView.h"

// #include "Timeline/Objects/Timeline_Object.h"
// #include "Timeline/Objects/Timeline_PlaybackRegion.h"
// #include "Timeline/Objects/Timeline_RegionSequence.h"
// #include "Timeline/Objects/Timeline_Document.h"

// #include "../Source/Test_Timeline/Test_RegionSequence.h"
// #include "../Source/Test_Timeline/Test_PlaybackRegion.h"



// /**
// 	A main locus of focus should be to verify instantiation of all the Timeline::Views for each Timeline::Object
	
// 	However the abstractive Timeline::Document instance is populated, be it by test or ARA or some other subclass, 
 
// */
// class ViewTester
// {
// public:
// 	ViewTester()
// 	{
		
// 	}
// 	~ViewTester(){}

// 	// refers to child components of the docView
// 	int getNumSequenceChildren(Timeline::DocumentView& docView)
// 	{
// 		int sequenceChildren = 0;
		
// 		for(int i = 0; i < docView.getNumChildComponents(); ++i)
// 		{
// 			juce::Component* child = docView.getChildComponent(i);
// 			if(dynamic_cast<Timeline::RegionSequenceView*>(child) != nullptr)
// 			{
// 				sequenceChildren++;
// 			}
// 		}
		
// 		return sequenceChildren;
// 	}
	
// 	int getNumZoomStateListeners(Timeline::DocumentView& docView)
// 	{
// 		return (int)getZoomStateListeners(docView).size();
// 	}
	
// 	//
// 	juce::Array<juce::Component*> getZoomStateListeners (Timeline::DocumentView& docView)
// 	{
// 		juce::Array<juce::Component*> zoomStateListeners;
		
// 		for(int i = 0; i < docView.getNumChildComponents(); i++)
// 		{
// 			juce::Component* childComponent = docView.getChildComponent(i);
// 			if(dynamic_cast<Timeline::ZoomStateListener*>(childComponent) != nullptr)
// 			{
// 				zoomStateListeners.add(childComponent);
// 			}
// 		}
		
// 		return zoomStateListeners;
// 	}
	

// 	//
// 	juce::Array<juce::Component*> getZoomStateListeners (Timeline::TimelineSection& timelineSection)
// 	{
// 		juce::Array<juce::Component*> zoomStateListeners;
		
// 		for(int i = 0; i < timelineSection.getNumChildComponents(); i++)
// 		{
// 			juce::Component* childComponent = timelineSection.getChildComponent(i);
// 			if(dynamic_cast<Timeline::ZoomStateListener*>(childComponent) != nullptr)
// 			{
// 				zoomStateListeners.add(childComponent);
// 			}
// 		}
		
// 		return zoomStateListeners;
// 	}
	
// 	void addRegionSequence(Timeline::RegionSequence* newSequence)
// 	{

// 	}

// private:
// };

// /**
// 	This class is a quick way to make Timeline::Documents for testing purposes
//  */
// class DocumentFactory
// {
// public:
// 	DocumentFactory()
// 	{
		
// 	}
	
// 	~DocumentFactory()
// 	{
		
// 	}
	
// 	std::unique_ptr<Timeline::Document> createDocument(int numSequences, int numRegions)
// 	{
// 		auto document = std::make_unique<Timeline::Document>(); ;

// 		for(size_t i = 0; i < (size_t) numSequences; i++)
// 		{
// 			auto sequence = new Timeline::RegionSequence();
// 			for(size_t j = 0; j < (size_t) numRegions; j++)
// 			{
// 				auto region = new Test::PlaybackRegion();
// 				juce::int64 startSample = j * 20;
// 				juce::int64 endSample = startSample + 10;
// 				region->setRangeInTimeline(startSample, endSample);
				
// 				sequence->addPlaybackRegion(region);
// 			}
// 			document->addRegionSequence(sequence);
// 		}
		
// 		return document;
// 	}
// };

// //==========================
// TEST_CASE("Testing DocumentFactory")
// {
// 	DocumentFactory docFactory;
// 	auto document = docFactory.createDocument(3, 4);
	
// 	auto sequences = document->getRegionSequences();
// 	REQUIRE(sequences.size() == 3);
// 	for(auto sequence : sequences)
// 	{
// 		auto regions = sequence->getPlaybackRegions();
// 		REQUIRE(regions.size() == 4);
// 	}
// }


// //=======================================
// TEST_CASE("Can add/remove RegionSequenceViews to DocumentView")
// {
// 	juce::ScopedJuceInitialiser_GUI guiInitializer;
	
// 	Timeline::ZoomState zoomState;
// 	//
// 	auto docView = std::make_unique<Timeline::DocumentView>();
// 	ViewTester viewTester;
	
	
// 	// Make up some
// 	auto regionSequence = std::make_unique<Test::RegionSequence>();
// 	regionSequence->addRegionAtRange(0, 1000);
// 	regionSequence->addRegionAtRange(1200, 15000);
// 	regionSequence->addRegionAtRange(19000, 200000);
	
	
	
// 	// Test Adding RegionSequence
// 	docView->_addRegionSequence(*regionSequence.get());
	
// 	// declare as function pointer to pass to juce::Timer and call after delay
// 	auto checkChildrenFunc = [&viewTester, docView = docView.get()]() {
// 		CHECK(viewTester.getNumSequenceChildren(*docView) == 1);
// 	};
// 	juce::Timer::callAfterDelay(10000, checkChildrenFunc);
	

	
// 	juce::MessageManager::getInstance()->runDispatchLoop();
// 	juce::MessageManager::deleteInstance();
// }
// //





// //==========================
// TEST_CASE("DocumentView builds from a Timeline::Document correctly")
// {
// 	juce::ScopedJuceInitialiser_GUI guiInitializer;
// 	// Helper class for checking our views got added, not just juce::components
// 	ViewTester viewTester;
	
// 	// Make Document
// 	DocumentFactory docFactory;
// 	int numSequences = 3;
// 	int numRegionsPerSequence = 4;
// 	auto document = docFactory.createDocument(numSequences, numRegionsPerSequence);
	
// 	// Make View
// 	auto docView = std::make_unique<Timeline::DocumentView>();

// 	// Give Document To View
// 	docView->updateDocument(*document.get());
	
// 	CHECK(viewTester.getNumSequenceChildren(*docView) == numSequences); // TODO: pass 3 by variable

// 	// 

	

	
// 	juce::MessageManager::getInstance()->runDispatchLoop();
// 	juce::MessageManager::deleteInstance();
// }


// //



// /** Might not be necessary if we don't use Timeline::Document to pass all the info to the DocumentView */
// TEST_CASE("Can make juce::var")
// {

// 	auto trackName = juce::String("Track 1");
// 	int regionNumber = 1;
	
// 	juce::DynamicObject::Ptr sequenceObject = new juce::DynamicObject();
// 	sequenceObject->setProperty("Track Name", trackName);

// 	juce::DynamicObject::Ptr regionObject = new juce::DynamicObject();
// 	regionObject->setProperty("Region Number", regionNumber);
	
// 	// Try adding regionObject as property of sequenceObject
// 	sequenceObject->setProperty("PlaybackRegion", juce::var(regionObject.get()));
	
// 	juce::var sequenceVar = juce::var(sequenceObject.get());
	
// 	REQUIRE(sequenceVar["Track Name"] == trackName);
// 	REQUIRE(sequenceVar.hasProperty("PlaybackRegion"));
// 	REQUIRE(sequenceVar["PlaybackRegion"] == juce::var(regionObject.get()));
	
// 	auto regionVar = sequenceVar["PlaybackRegion"];
// 	REQUIRE(regionVar.hasProperty("Region Number"));
// 	//regionSequence = nullptr;
// }


