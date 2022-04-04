/*
  ==============================================================================

    TurnTableComponent.h
    Created: 10 Mar 2022 5:11:23pm
    Author:  Alina Uzhvieva

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TurnTableComponent  : public juce::Component
{
public:
    TurnTableComponent();
    ~TurnTableComponent() override;

    // GUI rendering
    void paint (juce::Graphics&) override;
    void resized() override;
    
    // Logo
    Image logoImage;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TurnTableComponent)
};
