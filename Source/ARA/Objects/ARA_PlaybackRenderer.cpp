#include "ARA_PlaybackRenderer.h"

ARA_PlaybackRenderer::ARA_PlaybackRenderer(ARA::PlugIn::DocumentController* docController)
: juce::ARAPlaybackRenderer(docController)
{

}

bool ARA_PlaybackRenderer::processBlock(juce::AudioBuffer<float>& buffer, 
                      juce::AudioProcessor::Realtime realTime, 
                      const juce::AudioPlayHead::PositionInfo& positionInfo) noexcept 
{
    return false;
}