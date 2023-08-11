#include "ARA_DocumentController.h"
#include "ARA_PlaybackRenderer.h"
#include "ARA_AudioSource.h"
#include "../Timeline/Objects/Timeline_Document.h"
#include "../Timeline/Objects/Timeline_AudioSource.h"

//==============================================================================
juce::ARAPlaybackRenderer* ARA_DocumentController::doCreatePlaybackRenderer() noexcept
{
	return new juce::ARAPlaybackRenderer (getDocumentController());
}

//==============================================================================
juce::ARAAudioSource* ARA_DocumentController::doCreateAudioSource(juce::ARADocument* document, ARA::ARAAudioSourceHostRef hostRef)
{
	return new ARA_AudioSource(document, hostRef);
}

//==============================================================================
bool ARA_DocumentController::doRestoreObjectsFromStream (juce::ARAInputStream& input, const juce::ARARestoreObjectsFilter* filter) noexcept
{
	(void)input;
	(void)filter;
	// You should use this method to read any persistent data associated with
	// your ARA model graph stored in an archive using the supplied ARAInputStream.
	// Be sure to check the ARARestoreObjectsFilter to determine which objects to restore.
	return true;
}

bool ARA_DocumentController::doStoreObjectsToStream (juce::ARAOutputStream& output, const juce::ARAStoreObjectsFilter* filter) noexcept
{
	(void)output;
	(void)filter;
	// You should use this method to write any persistent data associated with
	// your ARA model graph into the an archive using the supplied ARAOutputStream.
	// Be sure to check the ARAStoreObjectsFilter to determine which objects to store.
	return true;
}

//==============================================================================
// This creates the static ARAFactory instances for the plugin.
const ARA::ARAFactory* JUCE_CALLTYPE createARAFactory()
{
	return juce::ARADocumentControllerSpecialisation::createARAFactory<ARA_DocumentController>();
}


Timeline::Document& ARA_DocumentController::getTimelineDocument() const
{
	return *mDocument.get();
}

void ARA_DocumentController::_updateDocument()
{
	mDocument.reset();
	mDocument = std::make_unique<Timeline::Document>();
}