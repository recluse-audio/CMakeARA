/*
  ==============================================================================

    AudioMod_ModificationProcessor.h
    Created: 10 Dec 2022 1:53:14pm
    Author:  Ryan Devens

  ==============================================================================
*/

/** 
 * This subclass of AudioProcessor has lots of unused variables being passed as parameters in the virtual functions 
 * of this class.  But we only really need this AudioProcessor for the sake of having an APVTS.  So ignore those.
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"


#pragma once
#include "../Util/Juce_Header.h"

namespace Timeline
{
/**
   This class is used to handle the Audio Processor business used by an Audio Mod
   such that it might be able to utilize an APVTS
 
*/
class ModificationProcessor : public juce::AudioProcessor
, public juce::ValueTree::Listener
{
public:
	ModificationProcessor(juce::UndoManager& undoManagerRef);
  ~ModificationProcessor() override;
  
  //==============================================================================
  void prepareToPlay (double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  #ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported (const BusesLayout& layouts) const override 
  {
    (void)layouts; //avoid warning 
    return false; 
  }
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
  void changeProgramName (int index, const juce::String& newName) override { }

  //==============================================================================
  void getStateInformation (juce::MemoryBlock& destData) override;
  void setStateInformation (const void* data, int sizeInBytes) override;

  juce::AudioProcessorValueTreeState& getValueTreeState();
    

private:
	double mSampleRate = -1;
	[[maybe_unused]] bool shouldUpdate = false;
	juce::AudioProcessorValueTreeState::ParameterLayout _createParameterLayout();
	juce::AudioProcessorValueTreeState valueTreeState;
	void valueTreePropertyChanged (juce::ValueTree& tree, const juce::Identifier& property) override;
};

}

#pragma GCC diagnostic pop