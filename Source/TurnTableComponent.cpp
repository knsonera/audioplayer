/*
  ==============================================================================

    TurnTableComponent.cpp
    Created: 10 Mar 2022 5:11:23pm
    Author:  Alina Uzhvieva

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TurnTableComponent.h"

//==============================================================================
TurnTableComponent::TurnTableComponent()
{
    // getting logo image
    logoImage = ImageCache::getFromMemory(BinaryData::turntable2_png, BinaryData::turntable2_pngSize);

}

TurnTableComponent::~TurnTableComponent()
{
}

// Making everything pretty
void TurnTableComponent::paint (juce::Graphics& g)
{

    g.fillAll (Colours::purple);   // clear the background

    g.setColour (Colours::purple);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    // draw app name
    g.setColour (juce::Colours::orange);
    g.setFont (34.0f);
    g.drawText ("OtoDecks", getWidth()/4, getHeight()/4, getWidth()/2, getHeight() / 10,
                Justification::centred, true);
    // draw app logo
    g.drawImage(logoImage, getWidth()/2-75, getHeight()/3+20, 150, 150, 0, 0, logoImage.getWidth(), logoImage.getWidth());
}

void TurnTableComponent::resized()
{
    // No child components
}
