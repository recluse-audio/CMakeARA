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
	using ARADocumentControllerSpecialisation::ARADocumentControllerSpecialisation;

protected:
	//==============================================================================
	// Override document controller customization methods here

	juce::ARAPlaybackRenderer* doCreatePlaybackRenderer() noexcept override;
	juce::ARAAudioSource* doCreateAudioSource(juce::ARADocument* document, ARA::AudioSourceARA::ARAAudioSourceHostRef hostRef)) override;

	bool doRestoreObjectsFromStream (juce::ARAInputStream& input, const juce::ARARestoreObjectsFilter* filter) noexcept override;
	bool doStoreObjectsToStream (juce::ARAOutputStream& output, const juce::ARAStoreObjectsFilter* filter) noexcept override;
	
	/**
	 * @brief I think this is a critical function.  
	 * It is where an ARA::Document becomes a Timeline::Document.  
	 * Accomplishing this is a big step towards test coverage, as the Timeline::Objects have Catch2 coverage
	 * and are easier to write tests for / instantiate in a standalone.
	 * 
	 * However, this needs coverage at some level to ensure that we aren't losing objects along the way
	 * @return Timeline::Document* 
	 */
	Timeline::Document& getTimelineDocument() const override;
private:
	std::unique_ptr<Timeline::Document> mDocument;
	void _updateDocument();
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARA_DocumentController)
};
