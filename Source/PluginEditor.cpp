#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "WaveCache/WaveformCache.h"
#include "ARA_View/PlaybackRegionView.h"
#include "ARA/ARA_DocumentController.h"

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor& p)
: AudioProcessorEditor (&p)
, AudioProcessorEditorARAExtension(&p)
, mProcessor (p)
{
    juce::ignoreUnused (mProcessor);

	waveCache = std::make_unique<WaveformCache>();
	
	setResizable(true, true);
    setSize (400, 300);
}

PluginEditor::~PluginEditor()
{
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
	if(mProcessor.isBoundToARA())
		g.drawFittedText ("ARA Plugin!", getLocalBounds(), juce::Justification::centred, 1);
	else
		g.drawFittedText ("NOT ARA Plugin!", getLocalBounds(), juce::Justification::centred, 1);
}

void PluginEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

juce::ARADocument* PluginEditor::getARADocument()
{
	juce::ARADocument* araDocument = nullptr;
	
	auto specialisation = this->getARADocumentController();
	if(specialisation != nullptr)
	{
		araDocument = specialisation->getDocument();
		return araDocument;
	}
	
	jassert(araDocument != nullptr);
	return araDocument;
}

ARA_DocumentController* PluginEditor::getARADocumentController()
{
	ARA_DocumentController* docController = nullptr;
	
	if (auto* editorView = this->getARAEditorView())
	{
		docController = ARADocumentControllerSpecialisation::getSpecialisedDocumentController<ARA_DocumentController>(editorView->getDocumentController());
		return docController;
		
	}
	
	return docController;
}

WaveformCache* PluginEditor::getWaveformCache()
{
	return waveCache.get();
}
