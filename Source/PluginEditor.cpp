#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "EditorState.h"
#include "WaveCache/WaveformCache.h"
#include "ARA/Views/PlaybackRegionView.h"
#include "Timeline/Objects/Timeline_Document.h"
#include "MainView/MainView.h"
#include "Sections/TimelineSection.h"

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
	
	mTestButton =  std::make_unique<juce::TextButton>("TEST BUTTON");
	mTestButton->addListener(this);
	mTestButton->setAlwaysOnTop(true);
	addAndMakeVisible(mTestButton.get());
	
	setResizable(true, true);
    this->setSize(mEditorState->mDefaultWidth, mEditorState->mDefaultHeight);
	mMainView->setBounds(0, 0, mEditorState->mDefaultWidth, mEditorState->mDefaultHeight);

	this->loadDocumentInTimeline(mProcessor.getDocument());
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

	mTestButton->setBoundsRelative(0.05f, 0.9f, 0.05f, 0.08f);
}



//===============
WaveformCache* PluginEditor::getWaveformCache()
{
	return waveCache.get();
}

//===============
void PluginEditor::loadDocumentInTimeline(Timeline::Document &document)
{
	auto timelineSection = dynamic_cast<Timeline::TimelineSection*>(mMainView->findChildWithID("TimelineSection"));
	if(timelineSection != nullptr)
		timelineSection->loadDocument(document);
}

//===============
void PluginEditor::buttonClicked(juce::Button *b)
{
	if(b == mTestButton.get())
	{
		auto document = mProcessor.getDocument();
		loadDocumentInTimeline(document);
	}
}
