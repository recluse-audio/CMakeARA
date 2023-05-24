#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "EditorState.h"
#include "WaveCache/WaveformCache.h"
#include "ARA/Views/PlaybackRegionView.h"
#include "ARA/Objects/ARA_DocumentController.h"
#include "MainView/MainView.h"
//==============================================================================
PluginEditor::PluginEditor (PluginProcessor& p)
: AudioProcessorEditor (&p)
, AudioProcessorEditorARAExtension(&p)
, mProcessor (p)
{
	mEditorState = std::make_unique<EditorState>(*this);
	
    juce::ignoreUnused (mProcessor);

	waveCache = std::make_unique<WaveformCache>();
	mMainView = std::make_unique<MainView>();
	addAndMakeVisible(mMainView.get());
	
	setResizable(true, true);
	mMainView->setSize(mEditorState->mDefaultWidth, mEditorState->mDefaultHeight);
    this->setSize(mEditorState->mDefaultWidth, mEditorState->mDefaultHeight);
}

PluginEditor::~PluginEditor()
{
	mMainView.reset();
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


//=================================
void PluginEditor::resized()
{
	auto scaleFactor = (float)getWidth() / mEditorState->mDefaultWidth;
	mEditorState->setEditorScaleFactor(scaleFactor);
	mMainView->setTransform(mEditorState->getScaleTransform());

}


//=================================
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
		docController = juce::ARADocumentControllerSpecialisation::getSpecialisedDocumentController<ARA_DocumentController>(editorView->getDocumentController());
		return docController;
		
	}
	
	return docController;
}

WaveformCache* PluginEditor::getWaveformCache()
{
	return waveCache.get();
}

