#pragma once
#include <Util/Juce_Header.h>
#include "Timeline/ZoomState/ZoomState.h"

namespace Timeline
{

/**
 * @brief This class represents a zoom in and zoom out button and their callbacks
 * 
 */
class ZoomControls : public juce::Component
                    , public juce::Button::Listener
{
public:
    ZoomControls(Timeline::ZoomState& zoomState) : mZoomState(zoomState)
    {
        mZoomInButton = std::make_unique<juce::TextButton>("Zoom In");
        mZoomInButton->setButtonText("+");
        mZoomInButton->addListener(this);
        addAndMakeVisible(*mZoomInButton.get());

        mZoomOutButton = std::make_unique<juce::TextButton>("Zoom Out");
        mZoomOutButton->setButtonText("-");
        mZoomOutButton->addListener(this);
        addAndMakeVisible(*mZoomOutButton.get());

        this->setSize(100, 40);
        mZoomInButton->setBounds(10, 5, 30, 30);
        mZoomOutButton->setBounds(60, 5, 30, 30);
    }
    ~ZoomControls() override
    {
        mZoomInButton->removeListener(this);
        mZoomOutButton->removeListener(this);
    }

    void buttonClicked(juce::Button* b) override
    {
        if(b == mZoomInButton.get())
            mZoomState.zoomIn();
        if(b == mZoomOutButton.get())
            mZoomState.zoomOut();
    }

private:
    Timeline::ZoomState& mZoomState;
    std::unique_ptr<juce::TextButton> mZoomInButton;
    std::unique_ptr<juce::TextButton> mZoomOutButton;


};

}