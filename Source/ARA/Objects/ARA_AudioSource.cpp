#include "ARA_AudioSource.h"

using Int64Range = juce::Range<juce::int64>;

ARA_AudioSource::ARA_AudioSource(juce::ARADocument* document, ARA::ARAAudioSourceHostRef hostRef)
: juce::ARAAudioSource(document, hostRef)
{

}

bool ARA_AudioSource::readFromAudioSource(juce::AudioBuffer<float>& buffer, Int64Range rangeToRead)
{
    return true;
}

juce::int64 ARA_AudioSource::getDurationInSamples() const
{
    return 0;
}