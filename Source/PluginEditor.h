#pragma once

#include "PluginProcessor.h"

class PlaybackRegionView;
class ARA_DocumentController;

class WaveformCache;
//==============================================================================
class PluginEditor  : public juce::AudioProcessorEditor
, public juce::AudioProcessorEditorARAExtension
, public juce::ARADocument::Listener
{
public:
    explicit PluginEditor (PluginProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
	
	juce::ARADocument* getARADocument();
	ARA_DocumentController* getARADocumentController();
	// Resets regionView to display the most recent PlaybackRegion
	void refreshRegionView();
	WaveformCache* getWaveformCache();
private:
	std::unique_ptr<WaveformCache> waveCache;
	std::unique_ptr<PlaybackRegionView> regionView;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& mProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
