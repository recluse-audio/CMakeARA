#include "Timeline_Document.h"
#include "Timeline_DocumentController.h"
#include "Timeline_AudioSource.h"

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
