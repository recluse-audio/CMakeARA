#pragma once
#include <Util/Juce_Header.h>


// save some typing
using Int64Range = juce::Range<juce::int64>;

namespace Timeline
{

/**
 Base class for Timeline::Objects such as the PlaybackRegion / AudioSource, etc.
*/
class Object : public juce::DynamicObject
{
public:
	Object()
	{
		for(int i = 0; i < 10; i++)
		{
			mDynamicObjects.add(std::make_unique<juce::DynamicObject>());
		}
	}
	~Object(){}
	

	//virtual juce::var toVar() = 0;
	juce::var toVar()
	{
		
	}


private:
	juce::Array<juce::DynamicObject> mDynamicObjects;
	
	
};




}

