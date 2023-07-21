#include "Timeline_AudioModification.h"
#include "Timeline_AudioProcessor/Timeline_ModificationProcessor.h"


using namespace Timeline;

AudioModification::AudioModification(juce::UndoManager& undoManagerRef)
{
	modColour = generateRandomColour();
	
	mProcessor = std::make_unique<Timeline::ModificationProcessor>(undoManagerRef);
}

AudioModification::~AudioModification()
{
	
}

juce::Colour AudioModification::generateRandomColour()
{
	auto randomValue = juce::Random();
	auto r = (juce::uint8)randomValue.nextInt(255);
	auto g = (juce::uint8)randomValue.nextInt(255);
	auto b = (juce::uint8)randomValue.nextInt(255);
	
	juce::Colour randomColour = {r, g, b};
	
	return randomColour;
	
}

juce::AudioProcessorValueTreeState& AudioModification::getValueTreeState()
{
	return mProcessor->getValueTreeState();
}

void AudioModification::setParameterValue(juce::Identifier paramID, float value)
{
	auto param = mProcessor->getValueTreeState().getParameter(paramID);
	param->setValue(value);

}

float AudioModification::getParameterValue(juce::Identifier paramID) const
{
	auto parameter = mProcessor->getValueTreeState().getParameter(paramID);
	auto paramValue = parameter->getValue();
	return paramValue;
}
