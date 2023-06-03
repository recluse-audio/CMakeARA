#include <catch2/catch_test_macros.hpp>
#include "Timeline/ZoomState/ZoomState.h"
#include "Timeline/ZoomState/ZoomStateListener.h"
#include "Util/Juce_Header.h"
#include "TestUtils/TestUtils.h"

TEST_CASE("Test setting zoom state by pixel")
{
	Timeline::ZoomState zoomState;
	
	auto testHeightFactor = 2.0;
	auto testWidthFactor = 2.0;
	
	auto testHeight = zoomState.baseSequenceHeight * testHeightFactor;
	auto testPixPerSecond = zoomState.basePixelsPerSecond * testWidthFactor;
	
	zoomState.setSequenceHeight(testHeight);
	zoomState.setPixelsPerSecond(testPixPerSecond);
	
	CHECK(zoomState.getSequenceHeight() == testHeight);
	CHECK(zoomState.getPixelsPerSecond() == testPixPerSecond);
	
	SECTION("Should stay within zoomState max zoom level")
	{
		// ridiculously huge values
		auto hugeSequenceHeight = 10000;
		auto hugePixelsPerSecond = 10000;
		
		zoomState.setSequenceHeight(hugeSequenceHeight);
		zoomState.setPixelsPerSecond(hugePixelsPerSecond);
		
		auto maxSequenceHeight = zoomState.baseSequenceHeight * zoomState.maxZoom;
		auto maxPixelsPerSecond = zoomState.basePixelsPerSecond * zoomState.maxZoom;
		
		CHECK(zoomState.getSequenceHeight() == maxSequenceHeight);
		CHECK(zoomState.getPixelsPerSecond() == maxPixelsPerSecond);
	}
	
	SECTION("Should stay within zoomState min zoom level")
	{
		auto minSequenceHeight = zoomState.baseSequenceHeight * zoomState.minZoom;
		auto minPixelsPerSecond = zoomState.basePixelsPerSecond * zoomState.minZoom;
		
		auto smallSequenceHeight = minSequenceHeight - 1;
		auto smallPixelsPerSecond = minPixelsPerSecond - 1;
		
		zoomState.setSequenceHeight(smallSequenceHeight);
		zoomState.setPixelsPerSecond(smallPixelsPerSecond);
		

		
		CHECK(zoomState.getSequenceHeight() == minSequenceHeight);
		CHECK(zoomState.getPixelsPerSecond() == minPixelsPerSecond);
	}
	
//	SECTION("Setting Sequence height should update mHeightFactor")
//	{
//		auto doubleBaseNumPixels = zoomState.basePixelsPerSecond * 2.0;
//
//		// set pixels per second equal to double the base
//		zoomState.setPixelsPerSecond(doubleBaseNumPixels);
//
//		CHECK(zoomState.getWidthFactor() == 2.0);
//	}
//
//	SECTION("Setting pixelsPerSecond should update mWidthFactor")
//	{
//		auto doubleBaseNumPixels = zoomState.basePixelsPerSecond * 2.0;
//
//		// set pixels per second equal to double the base
//		zoomState.setPixelsPerSecond(doubleBaseNumPixels);
//
//		CHECK(zoomState.getWidthFactor() == 2.0);
//	}
}


TEST_CASE("Setting zoom state by zoom factor")
{
	Timeline::ZoomState zoomState;
	
	auto testHeightFactor = 2.0;
	auto testWidthFactor = 2.0;
	
	zoomState.setHeightZoomFactor(testHeightFactor);
	zoomState.setWidthZoomFactor(testWidthFactor);
	
	CHECK(zoomState.getHeightZoomFactor() == testHeightFactor);
	CHECK(zoomState.getWidthZoomFactor() == testWidthFactor);
	
	SECTION("only set zoom levels below maxZoom constant")
	{
		auto invalidHeightFactor = zoomState.maxZoom + 1;
		auto invalidWidthFactor = zoomState.maxZoom + 1;
		
		zoomState.setHeightZoomFactor(invalidHeightFactor);
		zoomState.setWidthZoomFactor(invalidWidthFactor);
		
		CHECK(zoomState.getHeightZoomFactor() == zoomState.maxZoom);
		CHECK(zoomState.getWidthZoomFactor() == zoomState.maxZoom);
		
	}
	
	SECTION("only set zoom levels above minZoom constant")
	{
		auto invalidHeightFactor = zoomState.minZoom - 1;
		auto invalidWidthFactor = zoomState.minZoom - 1;
		
		zoomState.setHeightZoomFactor(invalidHeightFactor);
		zoomState.setWidthZoomFactor(invalidWidthFactor);
		
		CHECK(zoomState.getHeightZoomFactor() == zoomState.minZoom);
		CHECK(zoomState.getWidthZoomFactor() == zoomState.minZoom);
		
	}
}





//=================================================
//
//			ZOOM STATE LISTENER
//
//=================================================

//class TestZoomer : public juce::ChangeListener
//{
//public:
//	TestZoomer()
//	{
//		
//	}
//	
//	
//	void changeListenerCallback(juce::ChangeBroadcaster* source) override
//	{
//		auto zoomState = static_cast<Timeline::ZoomState*>(source);
//		if(zoomState != nullptr)
//		{
//			sequenceHeight = zoomState->getSequenceHeight();
//			pixelsePerSecond = zoomState->getPixelsPerSecond();
//		}
//	}
////	void updateZoomState(Timeline::ZoomState* zoomState) override
////	{
////		sequenceHeight = zoomState->getSequenceHeight();
////		pixelsePerSecond = zoomState->getPixelsPerSecond();
////	}
//	
//	double sequenceHeight = Timeline::ZoomState::baseSequenceHeight;
//	double pixelsePerSecond = Timeline::ZoomState::basePixelsPerSecond;
//	
//};
//
//
//
//TEST_CASE("ZoomStateListeners are being passed the ZoomState pointer we think we are passing it.")
//{
//	juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();
//	
//	Timeline::ZoomState zoomState;
//	TestZoomer zoomListener;
//	
//	zoomState.addChangeListener(&zoomListener);
//	
//	auto testSequenceHeight = Timeline::ZoomState::baseSequenceHeight * 2;
//	auto testPixelsPerSecond = Timeline::ZoomState::basePixelsPerSecond * 2;
//	
//	zoomState.setSequenceHeight(testSequenceHeight);
//	// Delay to allow message processing
//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//	CHECK(zoomListener.sequenceHeight == testSequenceHeight);
//
//	zoomState.setPixelsPerSecond(testPixelsPerSecond);
//	CHECK(zoomListener.pixelsePerSecond == testPixelsPerSecond);
//	
//	
//	juce::MessageManager::deleteInstance();
//}
