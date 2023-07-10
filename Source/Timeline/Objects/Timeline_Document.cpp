#include "Timeline_Document.h"
#include "Timeline_DocumentController.h"
#include "Timeline_AudioSource.h"
#include "Timeline_RegionSequence.h"

using namespace Timeline;

Document::Document()
{
	
}

Document::~Document()
{
	mRegionSequences.clear();
}

void Document::addRegionSequence(Timeline::RegionSequence *pSequence)
{
	mRegionSequences.push_back(pSequence);
}

std::vector<Timeline::RegionSequence*> Document::getRegionSequences()
{
	return mRegionSequences;
}


//==============
void Document::setPlaybackSampleRate(double sampleRate)
{
	mPlaybackSampleRate = sampleRate;
}

//==============
double Document::getPlaybackSampleRate() const
{
	return mPlaybackSampleRate;
}


double Document::getTimelineLength() const
{
	double length = minTimelineLength; // atleast 120 seconds
	for(auto sequence : mRegionSequences)
	{
		auto sequenceEnd = sequence->getEndOfFinalRegion() / mPlaybackSampleRate;
		if(sequenceEnd > length)
			length = sequenceEnd;
	}
	return length;
}


//======================
int Document::getNumSequences() const
{
	return (int)mRegionSequences.size();
}
