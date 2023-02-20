#include "ARA_DocumentController.h"
#include "ARA_PlaybackRenderer.h"

//==============================================================================
juce::ARAPlaybackRenderer* ARA_DocumentController::doCreatePlaybackRenderer() noexcept
{
	return new juce::ARAPlaybackRenderer (getDocumentController());
}

//==============================================================================
bool ARA_DocumentController::doRestoreObjectsFromStream (juce::ARAInputStream& input, const juce::ARARestoreObjectsFilter* filter) noexcept
{
	// You should use this method to read any persistent data associated with
	// your ARA model graph stored in an archive using the supplied ARAInputStream.
	// Be sure to check the ARARestoreObjectsFilter to determine which objects to restore.
	return true;
}

bool ARA_DocumentController::doStoreObjectsToStream (juce::ARAOutputStream& output, const juce::ARAStoreObjectsFilter* filter) noexcept
{
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
