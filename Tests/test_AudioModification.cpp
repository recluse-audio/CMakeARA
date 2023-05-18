#include <catch2/catch_test_macros.hpp>
#include "Timeline/Timeline_AudioModification.h"
#include "Util/Juce_Header.h"
#include "TestUtils/TestUtils.h"

using Int64Range = juce::Range<juce::int64>;

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
	//juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();

	juce::UndoManager undoManager;
	auto audioMod = std::make_unique<Timeline::AudioModification>(undoManager);
	auto gainParam = audioMod->getValueTreeState().getParameter("GAIN");
	CHECK(gainParam != nullptr);
	
}
