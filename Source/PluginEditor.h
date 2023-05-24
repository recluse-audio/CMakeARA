#pragma once

#include "PluginProcessor.h"

class EditorState;
class MainView;
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

    void paint (juce::Graphics&) override;
    void resized() override;
	
	juce::ARADocument* getARADocument();
	ARA_DocumentController* getARADocumentController();

	WaveformCache* getWaveformCache();
	
private:
	std::unique_ptr<EditorState> mEditorState;
	std::unique_ptr<WaveformCache> waveCache;
	std::unique_ptr<MainView> mMainView;
    PluginProcessor& mProcessor;
		

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
