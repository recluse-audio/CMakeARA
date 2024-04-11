#include "ARA_DocumentController.h"
#include "ARA_PlaybackRenderer.h"
#include "ARA_AudioSource.h"
#include "ARA_AudioModification.h"
#include "ARA_PlaybackRegion.h"
#include "ARA_RegionSequence.h"
#include "../Timeline/Objects/Timeline_Document.h"
#include "../Timeline/Objects/Timeline_AudioSource.h"
#include "../Test_Utils/DocumentFactory.h"

//==============================================================================
ARA_DocumentController::ARA_DocumentController(const ARA::PlugIn::PlugInEntry* entry,
                                         	   const ARA::ARADocumentControllerHostInstance* instance)
: juce::ARADocumentControllerSpecialisation(entry, instance)
{
	mTimelineDocument.reset();
	mTimelineDocument = std::make_unique<Timeline::Document>();
}
//==============================================================================
juce::ARAPlaybackRenderer* ARA_DocumentController::doCreatePlaybackRenderer() noexcept
{
	return new ARA_PlaybackRenderer(getDocumentController());
}

//==============================================================================
juce::ARAAudioSource* ARA_DocumentController::doCreateAudioSource(juce::ARADocument* document, ARA::ARAAudioSourceHostRef hostRef) noexcept
{
	return new ARA_AudioSource(document, hostRef);
}

//==============================================================================
juce::ARAAudioModification* ARA_DocumentController::doCreateAudioModification (juce::ARAAudioSource* audioSource, ARA::ARAAudioModificationHostRef hostRef, const juce::ARAAudioModification* modToClone) noexcept
{
	return new ARA_AudioModification(audioSource, hostRef, modToClone, mUndoManager);
}

//==============================================================================
juce::ARARegionSequence* ARA_DocumentController::doCreateRegionSequence(juce::ARADocument* document,  ARA::ARARegionSequenceHostRef hostRef) noexcept
{
	return new ARA_RegionSequence(document, hostRef);
}

//==============================================================================
juce::ARAPlaybackRegion* ARA_DocumentController::doCreatePlaybackRegion(juce::ARAAudioModification* audioMod,  ARA::ARAPlaybackRegionHostRef hostRef) noexcept
{
	ARA_AudioSource* customAudioSource = audioMod->getAudioSource<ARA_AudioSource>();
	ARA_AudioModification* customAudioMod = dynamic_cast<ARA_AudioModification*>(audioMod);
	//ARA_AudioSource* audioSource = dynamic_cast<ARA_AudioSource*>(araSource);
	return new ARA_PlaybackRegion(customAudioSource, customAudioMod, hostRef);
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
	return *mTimelineDocument.get();
}

void ARA_DocumentController::_updateDocument()
{
	auto regionSequences = this->getDocument()->getRegionSequences<ARA_RegionSequence>();

	for(auto regionSequence : regionSequences)
	{
		mTimelineDocument->addRegionSequence(regionSequence);

	}


}