/*
  ==============================================================================

    ARA_RegionSequence.h
    Created: 2024-04-10
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <../Util/Juce_Header.h>
#include "../Timeline/Objects/Timeline_RegionSequence.h"


class ARA_RegionSequence : public juce::ARARegionSequence
                         , public Timeline::RegionSequence
{
public:
  ARA_RegionSequence(juce::ARADocument* document,  ARA::ARARegionSequenceHostRef hostRef);

private:

    
};
