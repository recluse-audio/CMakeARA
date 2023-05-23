/*
  ==============================================================================

	This file was auto-generated! (By the Projucer)

	It contains the basic framework code for an ARA document controller implementation.

  ==============================================================================
*/

#pragma once

#include <../Util/Juce_Header.h>

//==============================================================================
/**
*/
class ARA_DocumentController  : public juce::ARADocumentControllerSpecialisation
{
public:
	//==============================================================================
	using ARADocumentControllerSpecialisation::ARADocumentControllerSpecialisation;

protected:
	//==============================================================================
	// Override document controller customization methods here

	juce::ARAPlaybackRenderer* doCreatePlaybackRenderer() noexcept override;

	bool doRestoreObjectsFromStream (juce::ARAInputStream& input, const juce::ARARestoreObjectsFilter* filter) noexcept override;
	bool doStoreObjectsToStream (juce::ARAOutputStream& output, const juce::ARAStoreObjectsFilter* filter) noexcept override;
	

private:
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARA_DocumentController)
};
