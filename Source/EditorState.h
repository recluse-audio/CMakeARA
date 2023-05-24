#include "PluginEditor.h"

class EditorState
{
public:
	EditorState(PluginEditor& e) : mEditor(e)
	{
		
	}
	
	~EditorState()
	{
		
	}
	
	
	void saveDimensions(int inWidth, int inHeight)
	{
		mSavedWidth = inWidth;
		mSavedHeight = inHeight;
		
		
		mEditor.getConstrainer()->setFixedAspectRatio((float)mSavedWidth / (float)mSavedHeight);
		mEditor.getConstrainer()->setMinimumWidth(mSavedWidth/4);
		mEditor.getConstrainer()->setMinimumHeight(mSavedHeight/4);
		
	}
	
	juce::AffineTransform getScaleTransform()
	{
		return juce::AffineTransform::scale(mScaleFactor);
	}
	
	
	float getEditorScaleFactor()
	{
		return mScaleFactor;
	}
	
	/** resizing. Do not name this setScaleFactor(), that would override a base component method */
	void setEditorScaleFactor(float scale)
	{
		mScaleFactor = scale;
	}
	
	
	// Width and Height of the plugin before user has resized
	static constexpr int mDefaultWidth = 800;
	static constexpr int mDefaultHeight = 300;
	
private:
	PluginEditor& mEditor;
	
	// Width and Height of the plugin after user has resized and saved plugin state
	int mSavedWidth = mDefaultWidth;
	int mSavedHeight = mDefaultHeight;
	float mScaleFactor = 1.f;
};
