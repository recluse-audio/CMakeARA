
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
		emptySectionOutline,
		navigationOutline,
		timelineOutline,
		inspectOutline,
		numColors
	};
	
	static juce::Colour getColor(ColorID color)
	{
		jassert (color < ColorID::numColors);
		static const juce::Colour colorData[] =
		{
			juce::Colour(0xffffffff),	// emptySectionBkgd
			juce::Colour(0xff47535f),   // navigationBkgd
			juce::Colour(0xff123d4a), 	// timelineBkgd
			juce::Colour(0xff2d748a),	// inspectBkgd
			juce::Colour(0xffdddddd),	// emptySectionOutline
			juce::Colour(0xffbaae6e),	// navigationOutline
			juce::Colour(0xffbaae6e),	// timelineOutline
			juce::Colour(0xffbaae6e),	// inspectOutline

		};
		
		return colorData[(size_t)color];
	}
};
