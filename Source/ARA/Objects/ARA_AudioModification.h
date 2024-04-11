/*
  ==============================================================================

    ARA_AudioModification.h
    Created: 2024-04-10
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <../Util/Juce_Header.h>
#include "../Timeline/Objects/Timeline_AudioModification.h"


class ARA_AudioModification : public juce::ARAAudioModification
                            , public Timeline::AudioModification
{
public:
    // TODO: Consider a different constructor when there is a modToClone
    ARA_AudioModification(juce::ARAAudioSource* audioSource, ARA::ARAAudioModificationHostRef hostRef, 
                            const juce::ARAAudioModification* modToClone, juce::UndoManager& undoManager);
private:

    
};
