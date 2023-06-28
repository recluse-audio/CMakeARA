#pragma once

#include "PluginProcessor.h"

class EditorState;
class MainView;
class ARA_DocumentController;
class WaveformCache;

namespace Timeline
{
	class Document;
}

//==============================================================================
class PluginEditor  : public juce::AudioProcessorEditor
, public juce::AudioProcessorEditorARAExtension
, public juce::ARADocument::Listener
, public juce::Button::Listener
{
public:
    explicit PluginEditor (PluginProcessor&);
    ~PluginEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
	
	void buttonClicked(juce::Button* b) override;

	WaveformCache* getWaveformCache();
	
	void loadDocumentInTimeline(Timeline::Document& document);
	
private:
	std::unique_ptr<EditorState> mEditorState;
	std::unique_ptr<WaveformCache> waveCache;
	std::unique_ptr<MainView> mMainView;
    PluginProcessor& mProcessor;
		
	std::unique_ptr<juce::TextButton> mTestButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
