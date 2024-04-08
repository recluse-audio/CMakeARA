#include "Timeline_PlaybackRenderer.h"
#include "Timeline_PlaybackRegion.h"
#include "Timeline_AudioSource.h"

using namespace Timeline;

PlaybackRenderer::PlaybackRenderer()
{
	
}

PlaybackRenderer::~PlaybackRenderer()
{
	
}

void PlaybackRenderer::doProcessBlock(juce::AudioBuffer<float>& processBlock,
                                    Int64Range blockRangeInTimeline)
{
    for(auto region : mPlaybackRegions)
    {
        auto renderRanges = region->getRenderRanges(blockRangeInTimeline);

        // don't do the work if the block isn't overlapping a PlaybackRegion
        if(!renderRanges.rangeInBlock.isEmpty())
        {
            /**
                1.) Read from AudioSource, write to regionBlock, 
                2.) Apply AudioModification, 
                3.) Add to processBlock
            */ 
            juce::AudioBuffer<float> regionBlock(processBlock.getNumChannels(), (int)renderRanges.rangeInBlock.getLength());

            _readFromAudioSource(regionBlock, blockRangeInTimeline, region);
            _applyAudioModification(regionBlock, region);
            _writeToProcessBlock(regionBlock, processBlock, renderRanges.rangeInBlock);
        }        
    
    }
}

void PlaybackRenderer::addPlaybackRegion(Timeline::PlaybackRegion* pRegion)
{
    mPlaybackRegions.push_back(pRegion);
}

int PlaybackRenderer::getNumRegions()
{
    return (int)mPlaybackRegions.size();
}


void PlaybackRenderer::_readFromAudioSource(juce::AudioBuffer<float>& bufferToWriteTo,
                                            Int64Range blockRangeInTimeline,
							                Timeline::PlaybackRegion* pRegion)
{
    auto audioSource = pRegion->getAudioSource();
    auto renderRanges = pRegion->getRenderRanges(blockRangeInTimeline);

    audioSource->readFromAudioSource(bufferToWriteTo, renderRanges.rangeInAudioSource);
    
}

void PlaybackRenderer::_applyAudioModification([[maybe_unused]] juce::AudioBuffer<float>& bufferToModify,
                                                [[maybe_unused]] Timeline::PlaybackRegion* pRegion)
{
    
}

void PlaybackRenderer::_writeToProcessBlock(juce::AudioBuffer<float>& regionBlock, 
                                            juce::AudioBuffer<float>& processBlock,
                                            Int64Range rangeToWriteTo)
{
    auto buffRead = regionBlock.getArrayOfReadPointers();
    auto buffWrite = processBlock.getArrayOfWritePointers();

    // using regionBlock numSamples  b/c running out of samples to read is worse than running out of indices to write to imho.  
    // keep garbage data out of processBlock at all costs! (although it would likely crash... I don't expect either circumstance to happen)
    for(int readIndex = 0; readIndex < regionBlock.getNumSamples(); readIndex++)
    {
        int writeIndex = readIndex + (int)rangeToWriteTo.getStart();
        for(int channel = 0; channel < regionBlock.getNumChannels(); channel++)
        {
            auto readSample = buffRead[channel][readIndex];
            buffWrite[channel][writeIndex] = readSample;
        }
    }
}