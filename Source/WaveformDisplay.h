/*
  ==============================================================================

    WaveformDisplay.h
    Created: 1 Mar 2022
    Author:  Alina Uzhvieva

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDisplay    : public Component, 
                           public ChangeListener
{
public:
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse );
    ~WaveformDisplay();

    // GUI rendering
    void paint (Graphics&) override;
    void resized() override;

    // Change Broadcaster
    void changeListenerCallback (ChangeBroadcaster *source) override;

    // Load audio URL
    void loadURL(URL audioURL);

    /* Set relative position to the playhead */
    void setPositionRelative(double pos);

private:
    AudioThumbnail audioThumb;
    bool fileLoaded; 
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
