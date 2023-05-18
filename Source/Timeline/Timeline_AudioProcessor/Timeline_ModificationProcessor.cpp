/*
  ==============================================================================

    AudioMod_ModificationProcessor.cpp
    Created: 10 Dec 2022 1:53:14pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "Timeline_ModificationProcessor.h"
#include "Timeline_UndoAction.h"

using namespace Timeline;

//=======================
ModificationProcessor::ModificationProcessor(juce::UndoManager& undoManagerRef) :
valueTreeState(*this, &undoManagerRef, "Audio Modification Value Tree", this->_createParameterLayout())
{
    valueTreeState.state.addListener(this);
}

//=======================
ModificationProcessor::~ModificationProcessor()
{
    valueTreeState.state.addListener(this);
}


//=======================
void ModificationProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    mSampleRate = sampleRate;
}

//=======================
void ModificationProcessor::releaseResources()
{
    
}

//=======================
void ModificationProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer)
{
    
}

//=======================
void ModificationProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    
}

//=======================
void ModificationProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    
}

//========================
juce::AudioProcessorValueTreeState& ModificationProcessor::getValueTreeState()
{
    return valueTreeState;
}

//========================
juce::AudioProcessorValueTreeState::ParameterLayout ModificationProcessor::_createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>("GAIN", "GAIN", 0.0f, 1.0f, 0.01f));
	//params.push_back (std::make_unique<juce::AudioParameterFloat>("FOCUS VIEW", "Focus View", 0.0f, 2.0f, 1.f));

    
    return { params.begin(), params.end() };
}

//==========================
void ModificationProcessor::valueTreePropertyChanged(juce::ValueTree& tree, const juce::Identifier& property)
{
    
}
