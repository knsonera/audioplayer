/*
  ==============================================================================

    DeckGUI.h
    Created: 23 Feb 2022
    Author:  Alina Uzhvieva

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
 Deck GUI Class
 Graphic user interface to control audio playback
*/

class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener,
                   public ChangeListener,
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(int sideNumber,
            DJAudioPlayer* player,
            PlaylistComponent* playlistComponent,
            AudioFormatManager & 	formatManagerToUse,
            AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    // GUI rendering
    void paint (Graphics&) override;
    void resized() override;

    // Event listeners
    void buttonClicked (Button *) override;
    void sliderValueChanged (Slider *slider) override;
    void changeListenerCallback (ChangeBroadcaster* source) override;

    // Drag & Drop
    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    // Playback timer
    void timerCallback() override;

private:
    int sideNumber;

    // Buttons
    ImageButton prevButton{"PREV"};
    ImageButton againButton{"0:00"};
    ImageButton playButton{"PLAY"};
    ImageButton stopButton{"STOP"};
    ImageButton loopButton{"LOOP"};
    ImageButton nextButton{"NEXT"};
    
    // Sliders
    Slider volSlider; 
    Slider speedSlider;
    Slider posSlider;
    
    // File chooser
    FileChooser chooser{"Select a file..."};

    // Waveform Display
    WaveformDisplay waveformDisplay;

    // Player
    DJAudioPlayer* player;
    PlaylistComponent* playlistComponent;
    
    // Current track info
    std::string currentTrackName = "";
    double currentTrackLength = 0.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
