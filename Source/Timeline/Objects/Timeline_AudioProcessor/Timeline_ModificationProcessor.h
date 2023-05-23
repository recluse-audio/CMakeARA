/*
  ==============================================================================

    AudioMod_ModificationProcessor.h
    Created: 10 Dec 2022 1:53:14pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include "../Util/Juce_Header.h"

namespace Timeline
{
/**
 This class is used to handle the Audio Processor business used by an Audio Mod
 such that it might be able to utilize an APVTS
 
 Have your AudioModification sub-class inherit from this if you want to use an APVTS with it
 
*/
class ModificationProcessor : public juce::AudioProcessor
, public juce::ValueTree::Listener
{
public:
	ModificationProcessor(juce::UndoManager& undoManagerRef);
    ~ModificationProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override { return false; }
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override { return nullptr; }
    bool hasEditor() const override { return false; }

    //==============================================================================
    const juce::String getName() const override { return " "; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override  { return false; }
    bool isMidiEffect() const override  { return false; }
    double getTailLengthSeconds() const override  { return 0.0; }

    //==============================================================================
    int getNumPrograms() override  { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int index) override { }
    const juce::String getProgramName (int index) override { return " "; }
    void changeProgramName (int index, const juce::String& newName) override { };

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& getValueTreeState();
    

private:
	double mSampleRate = -1;
	bool shouldUpdate = false;
	juce::AudioProcessorValueTreeState::ParameterLayout _createParameterLayout();
	juce::AudioProcessorValueTreeState valueTreeState;
	void valueTreePropertyChanged (juce::ValueTree& tree, const juce::Identifier& property) override;
};

}