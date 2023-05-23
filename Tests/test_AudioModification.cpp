#include <catch2/catch_test_macros.hpp>
#include "Util/Juce_Header.h"
#include "TestUtils/TestUtils.h"
#include "Timeline/Objects/Timeline_AudioModification.h"


using Int64Range = juce::Range<juce::int64>;

/**
	I am going to assume that an ARA AudioModification can accurately return it's AudioSource and its PlaybackRegions
 
*/
TEST_CASE("Test Audio Mod generates valid colour")
{
	for(int i = 0; i < 100; i++)
	{
		auto colour = Timeline::AudioModification::generateRandomColour();
		CHECK(colour.getFloatRed() >= 0.f);
		CHECK(colour.getFloatRed() <= 1.f);

	}

}

TEST_CASE("Test adding a parameter to the audio mod and retrieving value tree")
{
	TestUtils::SetupAndTeardown setupAndTeardown;
	
	juce::UndoManager undoManager;
	auto audioMod = std::make_unique<Timeline::AudioModification>(undoManager);
	
	SECTION("Should at least have a GAIN parameter")
	{
		auto gainParam = audioMod->getValueTreeState().getParameter("GAIN");
		CHECK(gainParam != nullptr);
	}
	
	SECTION("Should be able to set/get parameters through AudioModification interface")
	{
		auto paramID = juce::String("GAIN");
		auto gainParam = audioMod->getValueTreeState().getParameter(paramID);

		auto expectedGain = 0.f;
		auto actualGain = 0.f;
		auto errorTolerance = 0.0001f;
		auto error = 0.f;
		
		// First set value explicity through parameter itself to ensure juce behavior
		expectedGain = 0.12f;
		gainParam->setValue(expectedGain);
		CHECK( gainParam->getValue() == 0.12f );

		// Then get value through our interface
		expectedGain = 0.3f;
		gainParam->setValue(expectedGain);
		actualGain = audioMod->getParameterValue(paramID);
		error = std::abs(actualGain - expectedGain);
		CHECK( error < errorTolerance );
		
		// Then set it through our interface
		expectedGain = 0.45f;
		audioMod->setParameterValue(paramID, expectedGain);
		actualGain = audioMod->getParameterValue(paramID);
		error = std::abs(actualGain - expectedGain);
		CHECK( error < errorTolerance );
		
	}

	
	
}

TEST_CASE("Test getting and setting parameters")
{
	
}
