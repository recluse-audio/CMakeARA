/**
 * @brief Created by Ryan Devens 08/10/2023
 * 
 */
#pragma once
#include <../Util/Juce_Header.h>
#include "../Timeline/Objects/Timeline_PlaybackRenderer.h"


class ARA_PlaybackRenderer : public juce::ARAPlaybackRenderer
                           , public Timeline::PlaybackRenderer
{
public:

    ARA_PlaybackRenderer(ARA::PlugIn::DocumentController* docController);

    bool processBlock(juce::AudioBuffer<float>& buffer, 
                      juce::AudioProcessor::Realtime realTime, 
                      const juce::AudioPlayHead::PositionInfo& positionInfo) noexcept override;



private:

};