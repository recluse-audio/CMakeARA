#include "Timeline_DocumentController.h"
#include "Timeline_AudioSource.h"
#include "Timeline_PlaybackRegion.h"
#include "Timeline_RegionSequence.h"
#include "Timeline_Document.h"

using namespace Timeline;

DocumentController::DocumentController()
{
	
}

DocumentController::~DocumentController()
{
	
}

void DocumentController::addAudioSource(Timeline::AudioSource* source)
{
	mDocument->audioSources.push_back(source);
}

void DocumentController::addRegionSequence(Timeline::RegionSequence* sequence)
{
	mDocument->regionSequences.push_back(sequence);
}

void DocumentController::addPlaybackRegion(Timeline::PlaybackRegion *region)
{
	mDocument->playbackRegions.push_back(region);
}
