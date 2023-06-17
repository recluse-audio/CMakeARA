#include <catch2/catch_test_macros.hpp>

#include "Util/Juce_Header.h"
#include "Test_Utils/TestUtils.h"

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

#include "../Source/Test_Timeline/Test_RegionSequence.h"
#include "../Source/Test_Timeline/Test_PlaybackRegion.h"



/**

 
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

	juce::Array<juce::Component*> getZoomStateListeners (TimelineSection& timelineSection)
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
	

private:
};



////=======================================
//TEST_CASE("Can add/remove RegionSequenceViews to DocumentView")
//{
//	juce::ScopedJuceInitialiser_GUI guiInitializer;
//	
//	//
//	auto docView = std::make_unique<Timeline::DocumentView>();
//	ViewTester viewTester;
//	
//	
//	// Make up some
//	auto regionSequence = std::make_unique<Test::RegionSequence>();
//	regionSequence->addRegionAtRange(0, 1000);
//	regionSequence->addRegionAtRange(1200, 15000);
//	regionSequence->addRegionAtRange(19000, 200000);
//	
//	
//	
//	// Test Adding RegionSequence
//	docView->addRegionSequence(*regionSequence.get());
//	auto checkChildrenFunc = [&viewTester, docView = docView.get()]() {
//		CHECK(viewTester.getNumSequenceChildren(*docView) == 1);
//	};
//	juce::Timer::callAfterDelay(100, checkChildrenFunc);
//	//-------------------------
//	
//	// Remove RegionSequence
//	
//	
//
//	
//	juce::MessageManager::getInstance()->runDispatchLoop();
//	juce::MessageManager::deleteInstance();
//}
//
//
////=========================================
//TEST_CASE("ViewportSections need to set all their child components that are ZoomStateListeners to listen to its ZoomState")
//{
////	juce::ScopedJuceInitialiser_GUI guiInitializer;
////
////	Timeline::ZoomState zoomState;
////	auto viewportSection = std::make_unique<Timeline::ViewportSection>(zoomState);
////	
////	juce::MessageManager::getInstance()->runDispatchLoop();
////	juce::MessageManager::deleteInstance();
//}
//
//
////=========================================
//TEST_CASE("TimelineSection sets horizontal/vertical zoom factors on all ")
//{
//	juce::MessageManager::getInstance();
//	
//	juce::ScopedJuceInitialiser_GUI guiInitializer;
//
//	juce::MessageManagerLock mmLock;
//	
//	auto timelineSection = std::make_unique<TimelineSection>();
//	
//	
//}



TEST_CASE("Can make juce::var")
{

	auto trackName = juce::String("Track 1");
	
	juce::DynamicObject::Ptr regionSequence = new juce::DynamicObject();
	
	regionSequence->setProperty("Track Name", trackName);
	
	juce::var sequenceVar = juce::var(regionSequence.get());
	
	REQUIRE(sequenceVar["Track Name"] == trackName);
	//regionSequence = nullptr;
}

// TODO: Move this to its own test_Objects.cpp or somewhere not here in GUI testing
TEST_CASE("Can convert Timeline::Object to juce::var")
{
	SECTION("Always return with property 'Object Pointer' mapped to a juce::DynamicObject::Ptr")
	{
		Timeline::Object timelineObject;
		juce::var timelineVar = timelineObject.toVar();
		
		REQUIRE(timelineVar.hasProperty("Type"));
		REQUIRE(timelineVar["Type"] == "Object");

	}
}
