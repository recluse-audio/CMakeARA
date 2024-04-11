/*
  ==============================================================================

	This file was auto-generated! (By the Projucer)

	It contains the basic framework code for an ARA document controller implementation.

  ==============================================================================
*/

#pragma once

#include <../Util/Juce_Header.h>
#include "../Timeline/Objects/Timeline_DocumentController.h"


//==============================================================================
/**
 * @brief This class is the bridge between the juce::ARADocControllerSpec and the Timeline::DocumentController
 * 
 */
class ARA_DocumentController  : public juce::ARADocumentControllerSpecialisation
							  , public Timeline::DocumentController
{
public:
	//==============================================================================
    ARA_DocumentController (const ARA::PlugIn::PlugInEntry* entry,
                                         const ARA::ARADocumentControllerHostInstance* instance);
protected:
	//==============================================================================
	// Override document controller customization methods here

	juce::ARAPlaybackRenderer* doCreatePlaybackRenderer() noexcept override;
	juce::ARAAudioSource* doCreateAudioSource(juce::ARADocument* document, ARA::ARAAudioSourceHostRef hostRef) noexcept override;
	juce::ARAAudioModification* doCreateAudioModification (juce::ARAAudioSource* audioSource, ARA::ARAAudioModificationHostRef hostRef, 
															const juce::ARAAudioModification* optionalModificationToClone) noexcept override;
	juce::ARARegionSequence* doCreateRegionSequence(juce::ARADocument* document,  ARA::ARARegionSequenceHostRef hostRef) noexcept override;
	juce::ARAPlaybackRegion* doCreatePlaybackRegion(juce::ARAAudioModification* audioModification, ARA::ARAPlaybackRegionHostRef hostRef) noexcept override;

	bool doRestoreObjectsFromStream (juce::ARAInputStream& input, const juce::ARARestoreObjectsFilter* filter) noexcept override;
	bool doStoreObjectsToStream (juce::ARAOutputStream& output, const juce::ARAStoreObjectsFilter* filter) noexcept override;
	
public:
	/**
	 * @brief I think this is a critical function.  
	 * It is where an ARA::Document becomes a Timeline::Document.  
	 * Accomplishing this is a big step towards test coverage, as the Timeline::Objects have Catch2 coverage
	 * and are easier to write tests for / instantiate in a standalone.
	 * 
	 * However, this needs coverage at some level to ensure that we aren't losing objects along the way
	 * @return Timeline::Document& 
	 */
	Timeline::Document& getTimelineDocument() const override;
private:
	juce::UndoManager mUndoManager;
	std::unique_ptr<Timeline::Document> mTimelineDocument;
	void _updateDocument();
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARA_DocumentController)
};
