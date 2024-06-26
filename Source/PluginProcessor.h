#pragma once

#include<Util/Juce_Header.h>

namespace Timeline
{
	class Document;
}
class DocumentFactory;
class ARA_DocumentController;

#if (MSVC)
#include "ipps.h"
#endif

class PluginProcessor : public juce::AudioProcessor
#if JucePlugin_Enable_ARA
 , public juce::AudioProcessorARAExtension
#endif
{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	
	Timeline::Document& getTimelineDocument();
	
private:
	std::unique_ptr<DocumentFactory>	mDocumentFactory;
	std::unique_ptr<Timeline::Document> mBlankDocument;

    // function to aid in access to our custom sub-class. cleans up the ARA rigamarole
    // MAY RETURN NULL!!!
    ARA_DocumentController* _getCustomDocumentController();
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
