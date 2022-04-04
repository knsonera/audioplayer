/*
  ==============================================================================

    PlaylistComponent.h
    Created: 4 Mar 2022
    Author:  Alina Uzhvieva

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "vector"
#include "string"

struct AudioTrack;

//==============================================================================
/*
 Playlist Component:
 Load audio files from folder, show information and play music in two players
*/
class PlaylistComponent  : public juce::Component,
                            public juce::TableListBoxModel,
                            public juce::Button::Listener,
                            public juce::TextEditor::Listener,
                            public juce::ChangeBroadcaster
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    // GUI representation
    void paint (juce::Graphics&) override;
    void resized() override;
    
    // return number of rows in playlist
    int getNumRows() override;
    
    // change playlist background
    void paintRowBackground (Graphics &,
                             int row,
                             int width,
                             int height,
                             bool rowIsSelected) override;
    
    // change appearance of table cell //
    void paintCell (Graphics &,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    
    // add components to cell (buttons) //
    Component* refreshComponentForCell (int rowNumber,
                                        int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    // event listeners - button click, cell click
    void buttonClicked(Button* button) override;
    void cellClicked (int rowNumber, int columnId, const MouseEvent& e) override;
    
    // text editor listener
    void textEditorTextChanged (TextEditor* editor);
    void textEditorReturnKeyPressed (TextEditor* editor);
    void textEditorEscapeKeyPressed (TextEditor* editor);
    void textEditorFocusLost (TextEditor* editor);
    
    // selected track and side
    AudioTrack getSelectedAudioTrack();
    int getSelectedSide();

private:
    
    TableListBox tableComponent;
    File savedPlaylist;
    
    // buttons
    TextButton loadButton{"Add to playlist"};
    TextButton removeAllButton{"Remove all"};
    
    // search textbox
    TextEditor searchTextEditor{};
    
    // Vector of all audio tracks in playlist
    std::vector<AudioTrack> audioTracks;
    std::vector<AudioTrack> savedAudioTracks;
    
    int selectedAudioTrackIndex = -1;
    int selectedSide = 1;
    
    // load files from directory
    void loadPlaylistDirectory();
    
    void searchTextEditorUpdated();
    void searchTextEditorRestore();

    void displayAudioTracks(std::vector<AudioTrack> audioTracks);
    void loadSavedPlaylist();
    void readPlaylist(const juce::File& fileToRead);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};

struct AudioTrack {
    std::string name;
    URL url;
    TextButton* side1Btn;
    TextButton* side2Btn;
    TextButton* removeBtn;
    std::string title;
    double lengthInSec;
};
