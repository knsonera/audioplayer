/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "TurnTableComponent.h"


//==============================================================================
/*
    This component lives inside the window, and this is where we should put all
    controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    
    // AudioSource functions:
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    // GUI rendering
    void paint (Graphics& g) override;
    void resized() override;

private:
    AudioDeviceManager customDeviceManager;
     
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100};
    
    // playlist
    PlaylistComponent playlistComponent;
    // logo
    TurnTableComponent turntableComponent;

    // players
    DJAudioPlayer player1{formatManager};
    DJAudioPlayer player2{formatManager};
    
    // decks
    DeckGUI deckGUI1{1, &player1, &playlistComponent, formatManager, thumbCache};
    DeckGUI deckGUI2{2, &player2, &playlistComponent, formatManager, thumbCache};

    MixerAudioSource mixerSource;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
