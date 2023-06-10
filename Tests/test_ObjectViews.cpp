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



//=======================================
TEST_CASE("Can add/remove RegionSequenceViews to DocumentView")
{
	juce::ScopedJuceInitialiser_GUI guiInitializer;
	
	//
	auto docView = std::make_unique<Timeline::DocumentView>();
	ViewTester viewTester;
	
	
	// Make up some
	auto regionSequence = std::make_unique<Test::RegionSequence>();
	regionSequence->addRegionAtRange(0, 1000);
	regionSequence->addRegionAtRange(1200, 15000);
	regionSequence->addRegionAtRange(19000, 200000);
	
	
	
	// Test Adding RegionSequence
	docView->addRegionSequence(*regionSequence.get());
	auto checkChildrenFunc = [&viewTester, docView = docView.get()]() {
		CHECK(viewTester.getNumSequenceChildren(*docView) == 1);
	};
	juce::Timer::callAfterDelay(100, checkChildrenFunc);
	//-------------------------
	
	// Remove RegionSequence
	
	
	docView.reset();
	regionSequence.reset();
	
	juce::MessageManager::getInstance()->runDispatchLoop();
	juce::MessageManager::deleteInstance();
}


//=========================================
TEST_CASE("ViewportSections need to set all their child components that are ZoomStateListeners to listen to its ZoomState")
{
	juce::ScopedJuceInitialiser_GUI guiInitializer;

	Timeline::ZoomState zoomState;
	auto viewportSection = std::make_unique<Timeline::ViewportSection>(zoomState);
	
}


//=========================================
TEST_CASE("TimelineSection sets horizontal/vertical zoom factors on all ")
{
	juce::ScopedJuceInitialiser_GUI guiInitializer;

	auto timelineSection = std::make_unique<TimelineSection>();
	
	juce::MessageManager::getInstance()->runDispatchLoop();
	juce::MessageManager::deleteInstance();
}

