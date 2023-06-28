#pragma once
#include "Util/Juce_Header.h"
#include "../Timeline/Objects/Timeline_RegionSequence.h"
#include "../Timeline/Objects/Timeline_Document.h"

#include "../Source/Test_Timeline/Test_PlaybackRegion.h"

/**
	This class is a quick way to make Timeline::Documents for testing purposes
 */
class DocumentFactory
{
public:
	DocumentFactory()
	{
		
	}
	
	~DocumentFactory()
	{
		
	}
	
	static std::unique_ptr<Timeline::Document> createDocument(int numSequences, int numRegions)
	{
		auto document = std::make_unique<Timeline::Document>();

//		auto sequence = new Timeline::RegionSequence();
//		auto region1 = new Test::PlaybackRegion();
//		region1->setRangeInTimeline(0, 88200);
//		auto region2 = new Test::PlaybackRegion();
//		region2->setRangeInTimeline(100000, 150000);
//
//		sequence->addPlaybackRegion(region1);
//		sequence->addPlaybackRegion(region2);
//		document->addRegionSequence(sequence);
		for(size_t i = 0; i < (size_t) numSequences; i++)
		{
			auto sequence = new Timeline::RegionSequence();
			for(size_t j = 0; j < (size_t) numRegions; j++)
			{
				juce::int64 regionStart = ((int)j * 5 ) * document->getPlaybackSampleRate();
				juce::int64 regionEnd = regionStart + document->getPlaybackSampleRate();
				auto region = new Test::PlaybackRegion();

				region->setRangeInTimeline(regionStart, regionEnd);

				sequence->addPlaybackRegion(region);
			}
			document->addRegionSequence(sequence);
		}
		
		return document;
	}
};
