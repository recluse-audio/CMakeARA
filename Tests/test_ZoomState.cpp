#include <catch2/catch_test_macros.hpp>

#include "Util/Juce_Header.h"
#include "TestUtils/TestUtils.h"

#include "Timeline/ZoomState/ZoomState.h"
#include "Timeline/ZoomState/ZoomStateListener.h"

#include "Timeline/Views/PlaybackRegionView.h"
#include "Timeline/Objects/Timeline_PlaybackRegion.h"
#include "TestTimeline/Test_PlaybackRegion.h"


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
		auto hugeSequenceHeight = 100000;
		auto hugePixelsPerSecond = 100000;
		
		zoomState.setSequenceHeight(hugeSequenceHeight);
		zoomState.setPixelsPerSecond(hugePixelsPerSecond);
		
		auto maxSequenceHeight = zoomState.baseSequenceHeight * zoomState.maxZoom;
		auto maxPixelsPerSecond = zoomState.basePixelsPerSecond * zoomState.maxZoom;
		
		CHECK(zoomState.getSequenceHeight() == maxSequenceHeight);
		CHECK(zoomState.getPixelsPerSecond() == maxPixelsPerSecond);
		CHECK(zoomState.getHeightZoomFactor() == zoomState.maxZoom);
		CHECK(zoomState.getWidthZoomFactor() == zoomState.maxZoom);
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
		CHECK(zoomState.getHeightZoomFactor() == zoomState.minZoom);
		CHECK(zoomState.getWidthZoomFactor() == zoomState.minZoom);
	}
	
	
	
	SECTION("Setting Sequence height should update mHeightFactor")
	{
		testHeightFactor = 3.0;
		auto testSequenceHeight = zoomState.baseSequenceHeight * testHeightFactor;

		// set pixels per second equal to double the base
		zoomState.setSequenceHeight(testSequenceHeight);

		CHECK(zoomState.getHeightZoomFactor() == testHeightFactor);
	}
	

	
	
	SECTION("Setting pixelsPerSecond should update mWidthFactor")
	{
		testWidthFactor = 3.0;
		auto testPixelsPerSecond = zoomState.basePixelsPerSecond * testWidthFactor;

		// set pixels per second equal to double the base
		zoomState.setPixelsPerSecond(testPixelsPerSecond);

		CHECK(zoomState.getWidthZoomFactor() == testWidthFactor);
	}
	
	
}

//===========================================
//
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
	
	SECTION("Setting heightZoomFactor should update sequence height")
	{
		testHeightFactor = 5.0;
		zoomState.setHeightZoomFactor(testHeightFactor);
		auto expectedSequenceHeight = zoomState.baseSequenceHeight * testHeightFactor;
		CHECK(zoomState.getSequenceHeight() == expectedSequenceHeight );
	}
	
	SECTION("Setting widthZoomFactor should update  pixels per second")
	{
		testWidthFactor = 5.0;
		zoomState.setWidthZoomFactor(testWidthFactor);
		auto expectedPixelsPerSecond = zoomState.basePixelsPerSecond * testWidthFactor;
		CHECK(zoomState.getPixelsPerSecond() == expectedPixelsPerSecond );
	}
}





//=================================================
//
//			ZOOM STATE LISTENER
//
//=================================================

class TestZoomer : public juce::ChangeListener
{
public:
	TestZoomer()
	{
		
	}
	
	
	void changeListenerCallback(juce::ChangeBroadcaster* source) override
	{
		auto zoomState = static_cast<Timeline::ZoomState*>(source);
		if(zoomState != nullptr)
		{
			sequenceHeight = zoomState->getSequenceHeight();
			pixelsePerSecond = zoomState->getPixelsPerSecond();
		}
	}
	
	double sequenceHeight = Timeline::ZoomState::baseSequenceHeight;
	double pixelsePerSecond = Timeline::ZoomState::basePixelsPerSecond;
	
};



TEST_CASE("ZoomStateListeners are being passed the ZoomState pointer we think we are passing it.")
{
	/** Needed for ChangeListener callback to work */
	juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();
	
	Timeline::ZoomState zoomState;
	TestZoomer zoomListener;
	
	zoomState.addChangeListener(&zoomListener);
	
	auto testSequenceHeight = Timeline::ZoomState::baseSequenceHeight * 2;
	auto testPixelsPerSecond = Timeline::ZoomState::basePixelsPerSecond * 2;
	
	zoomState.setSequenceHeight(testSequenceHeight);
	zoomState.setPixelsPerSecond(testPixelsPerSecond);
	
	//*********************************
	//************ IMPORTANT **********
	//*********************************
	/**
		This is the only way I've gotten a change listener test to work.
		Other solutions seems to get to the CHECK function call before the
		Asynchronous change message is broadcast
	 */
	zoomState.dispatchPendingMessages();
	
	
	CHECK(zoomListener.sequenceHeight == testSequenceHeight);
	CHECK(zoomListener.pixelsePerSecond == testPixelsPerSecond);
	
	
	/** Needed for ChangeListener callback to work (cleanup) */
	juce::MessageManager::deleteInstance();
}



//===============================
//
TEST_CASE("PlaybackRegionView can size correctly")
{
	/** Needed for ChangeListener callback to work */
	juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();

	Timeline::ZoomState zoomState;

	auto testRegion = std::make_unique<Test::PlaybackRegion>();
	testRegion->setRangeInTimeline(0, 1);
	testRegion->setRangeInAudioSource(0, 1);

	auto regionView = std::make_unique<Timeline::PlaybackRegionView>(*testRegion.get());

	zoomState.addChangeListener(regionView.get());

	auto testHeight = 200;
	auto testPixPer = 200;

	zoomState.setSequenceHeight(testHeight);
	zoomState.setPixelsPerSecond(testPixPer);

	//*********************************
	//************ IMPORTANT **********
	//*********************************
	/**
		This is the only way I've gotten a change listener test to work.
		Other solutions seems to get to the CHECK function call before the
		Asynchronous change message is broadcast
	 */
	zoomState.dispatchPendingMessages();


	auto regionBounds = regionView->getLocalBounds();
	CHECK(regionBounds.getWidth() == testPixPer);

	regionView.reset(nullptr);
	testRegion.reset();

	/** Needed for ChangeListener callback to work (cleanup) */
	juce::MessageManager::deleteInstance();
}
