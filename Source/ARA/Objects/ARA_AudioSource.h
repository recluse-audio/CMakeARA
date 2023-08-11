
/**
 * @brief Created by Ryan Devens 08/01/2023
 * 
 */
#pragma once
#include <../Util/Juce_Header.h>
#include "../Timeline/Objects/Timeline_AudioSource.h"

class ARA_AudioSource : public juce::ARAAudioSource
                      , public Timeline::AudioSource
{
public:
    ARA_AudioSource(juce::ARADocument* document, ARA::ARAAudioSourceHostRef hostRef);

    bool readFromAudioSource(juce::AudioBuffer<float>& buffer, juce::Range<juce::int64> rangeToRead) override;
    juce::int64 getDurationInSamples() const override;

};