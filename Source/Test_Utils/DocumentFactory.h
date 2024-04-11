#pragma once
#include "Util/Juce_Header.h"
#include "../Timeline/Objects/Timeline_RegionSequence.h"
#include "../Timeline/Objects/Timeline_Document.h"
#include "../Timeline/Objects/Timeline_AudioSource.h"
#include "../Timeline/Objects/Timeline_AudioModification.h"
#include "../Source/Test_Timeline/Test_PlaybackRegion.h"
#include "../Source/Test_Timeline/Test_AudioSource.h"


/**
	This class is a quick way to make Timeline::Documents for testing purposes
 */
class DocumentFactory
{
public:
	DocumentFactory()
	{
		mAudioSource = std::make_unique<Test::AudioSource>();
		mAudioMod = std::make_unique<Timeline::AudioModification>(mUndoManager);
	}
	
	~DocumentFactory()
	{
		
	}
	
	std::unique_ptr<Timeline::Document> createDocument(int numSequences, int numRegions)
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
				juce::int64 regionStart = ((int)j * 5 ) * (int)document->getPlaybackSampleRate();
				juce::int64 regionEnd = regionStart + (int)document->getPlaybackSampleRate();
				auto region = new Test::PlaybackRegion(mAudioSource.get(), mAudioMod.get());

				region->setRangeInTimeline(regionStart, regionEnd);

				sequence->addPlaybackRegion(region);
			}
			document->addRegionSequence(sequence);
		}
		
		return document;
	}
private:
	std::unique_ptr<Test::AudioSource> mAudioSource;
	std::unique_ptr<Timeline::AudioModification> mAudioMod;
	juce::UndoManager mUndoManager;
};
