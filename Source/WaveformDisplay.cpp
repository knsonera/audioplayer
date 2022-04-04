/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 1 Mar 2022
    Author:  Alina Uzhvieva
    Description: Audio data visualization

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & 	formatManagerToUse,
                                 AudioThumbnailCache & 	cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse), 
                                 fileLoaded(false), 
                                 position(0)
                          
{
  audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{
    g.fillAll (Colours::purple);   // clear the background

    // if file is loaded draw waveform for a channel
    g.setColour (Colours::orange);
    if(fileLoaded)
    {
      audioThumb.drawChannel(g, 
        getLocalBounds(), 
        0, 
        audioThumb.getTotalLength(), 
        0, 
        1.0f
      );
        
      // draw rectangle to show current playback position
      g.setColour(Colours::grey);
      g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight(), 2);
    }
    else 
    {
      // if no file loaded, show placeholder text
      g.setFont (20.0f);
      g.drawText ("File not loaded...", getLocalBounds(),
                  Justification::centred, true);

    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

// Load audio file by URL
void WaveformDisplay::loadURL(URL audioURL)
{
  audioThumb.clear();
  fileLoaded  = audioThumb.setSource(new URLInputSource(audioURL));
  if (fileLoaded)
  {
    std::cout << "wfd: loaded! " << std::endl;
    repaint();
  }
  else {
    std::cout << "wfd: not loaded! " << std::endl;
  }
}

// Repaint waveform on any audiothumb change
void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    repaint();
}

// Set relative position to the playhead
void WaveformDisplay::setPositionRelative(double pos)
{
  if (pos != position)
  {
    position = pos;
    repaint();
  }
}




