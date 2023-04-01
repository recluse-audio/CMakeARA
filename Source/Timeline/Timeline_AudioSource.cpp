
#include "Timeline_AudioSource.h"

using namespace Timeline;

AudioSource::AudioSource(juce::AudioBuffer<float> bufferSource)
{
	mBufferSource = std::make_unique<juce::AudioBuffer<float>>(bufferSource);
}

AudioSource::~AudioSource()
{
	
}

juce::int64 AudioSource::getDurationInSamples() const
{
	return mBufferSource->getNumSamples();
}


// juce::int64 AudioSource::getEndInAudioSource(juce::int64 startInSource, juce::int64 duration) const
// {
// 	auto sourceDuration = this->getDurationInSamples();
// 	auto endInSource = startInSource + duration;
// 	if(endInSource > sourceDuration)
// 		endInSource = sourceDuration;
// }

