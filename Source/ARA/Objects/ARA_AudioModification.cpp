#include "ARA_AudioModification.h"

ARA_AudioModification::ARA_AudioModification(juce::ARAAudioSource* audioSource, ARA::ARAAudioModificationHostRef hostRef, 
                                            const juce::ARAAudioModification* modToClone, juce::UndoManager& undoManager)
: juce::ARAAudioModification(audioSource, hostRef, modToClone)
, Timeline::AudioModification(undoManager)
{

}