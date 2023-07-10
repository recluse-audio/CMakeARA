#pragma once
#include "Util/Juce_Header.h"
#include "../Timeline/Objects/Timeline_AudioSource.h"
#include "../Timeline/Objects/Timeline_AudioModification.h"

#include "../Source/Test_Timeline/Test_PlaybackRegion.h"
#include "../Source/Test_Timeline/Test_AudioSource.h"

/**
	This class is a quick way to make Timeline::Objects
    "factory" is a bit of a misnomer.  This is just a
 */
class ObjectFactory
{
public:
    ObjectFactory()
    {
        mAudioSource = std::make_unique<Test::AudioSource>();
        mAudioMod = std::make_unique<Timeline::AudioModification>(mUndoManager);
        mRegion = std::make_unique<Test::PlaybackRegion>(*mAudioSource.get(), *mAudioMod.get());
    }

    ~ObjectFactory()
    {

    }

    // resizes audio source to numSamples and sets all of them to 1.f
    void generateAudioSource(int numSamples)
    {
        mAudioSource->generateWithAllOnes(1, numSamples);
    }

    Test::AudioSource* getAudioSource() const
    {
        return mAudioSource.get();
    }

    Timeline::AudioModification& getAudioModification() const
    {
        return *mAudioMod.get();
    }

    Test::PlaybackRegion& getPlaybackRegion() const
    {
        return *mRegion.get();
    }
private:
    std::unique_ptr<Test::AudioSource> mAudioSource;
    std::unique_ptr<Timeline::AudioModification> mAudioMod;
    std::unique_ptr<Test::PlaybackRegion> mRegion;
    juce::UndoManager mUndoManager;

};
