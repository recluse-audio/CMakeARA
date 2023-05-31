
/**
	All colors in plug-in defined here.
 */
class Colors
{
public:
	
	enum class ColorID
	{
		emptySectionBkgd, // used for sections that will be completely covered by child components
		navigationBkgd,
		timelineBkgd,
		inspectBkgd,
		playbackRegionBkgd,
		
		emptySectionOutline,
		navigationOutline,
		timelineOutline,
		inspectOutline,
		playbackRegionOutline,

		endOfList
	};
	
	static juce::Colour getColor(ColorID color)
	{
		jassert (color < ColorID::endOfList);
		static const juce::Colour colorData[] =
		{
			juce::Colour(0xffffffff),	// emptySectionBkgd
			juce::Colour(0xff47535f),   // navigationBkgd
			juce::Colour(0xff123d4a), 	// timelineBkgd
			juce::Colour(0xff2d748a),	// inspectBkgd
			juce::Colour(0xff2d748a),	// playbackRegionBkgd

			
			
			juce::Colour(0xffdddddd),	// emptySectionOutline
			juce::Colour(0xffbaae6e),	// navigationOutline
			juce::Colour(0xffbaae6e),	// timelineOutline
			juce::Colour(0xffbaae6e),	// inspectOutline
			juce::Colour(0xffdac9c9),	// playbackRegionOutline
			
			
			juce::Colour(0xff000000),   // endOfList


		};
		
		return colorData[(size_t)color];
	}
};
