/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 4 Mar 2022
    Author:  Alina Uzhvieva

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "DJAudioPlayer.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    
    double colW = 1000 / 10;
    
    File savedPlaylist(File::getCurrentWorkingDirectory().getChildFile("savedPlaylist.txt"));
    savedPlaylist.create();
    std::cout << savedPlaylist.existsAsFile() << std::endl;
    
    savedPlaylist.appendText("test");

    // Adding table structure: header and columns
    tableComponent.getHeader().addColumn("Track title", 1, colW*5);
    tableComponent.getHeader().addColumn("Duration", 2, colW*2);
    tableComponent.getHeader().addColumn("Deck 1", 3, colW);
    tableComponent.getHeader().addColumn("Deck 2", 4, colW);
    tableComponent.getHeader().addColumn("Remove", 5, colW);
    tableComponent.getHeader().setColour(TableHeaderComponent::backgroundColourId, Colours::purple);

    tableComponent.setModel(this);
    
    // Render table
    addAndMakeVisible(tableComponent);
    
    // Adding buttons and text box
    addAndMakeVisible(loadButton);
    addAndMakeVisible(removeAllButton);
    addAndMakeVisible(searchTextEditor);

}

PlaylistComponent::~PlaylistComponent()
{
    
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    
    g.fillAll (juce::Colours::darkorange);// background colour
    
    // draw purple text next to search box
    g.setColour (juce::Colours::purple);
    g.setFont (16.0f);
    g.drawText ("Search:", 470, 10, 200, 30,
                Justification::centredTop, true);
}

void PlaylistComponent::resized()
{
    // setting positions and bounds for all Playlist GUI elements
    loadButton.setBounds(0, 5, 200, 30);
    removeAllButton.setBounds(200, 5, 200, 30);
    searchTextEditor.setBounds(600, 5, getWidth(), 30);
    
    // change button colours
    loadButton.setColour(TextButton::buttonColourId, Colours::purple);
    removeAllButton.setColour(TextButton::buttonColourId, Colours::purple);
    searchTextEditor.setColour(TextEditor::backgroundColourId, Colours::peachpuff);
    searchTextEditor.setColour(TextEditor::textColourId, Colours::purple);
    searchTextEditor.setTextToShowWhenEmpty("Enter track title", Colours::grey);
    
    // event listeners
    loadButton.addListener(this);
    removeAllButton.addListener(this);
    searchTextEditor.addListener(this);
    
    searchTextEditor.onReturnKey = [this] { searchTextEditorUpdated(); };
    searchTextEditor.onTextChange = [this] { searchTextEditorRestore(); };
    
    // add table (playlist)
    tableComponent.setBounds(0, 40, getWidth(), getHeight());
}

// Search: Filter items that match the request
void PlaylistComponent::searchTextEditorUpdated()
{
    std::cout << "search text changed " << searchTextEditor.getText() << std::endl;
    if (searchTextEditor.getText().length() > 0)
    {
        std::vector<AudioTrack> foundAudioTracks;
        
        for (int i = 0; i < savedAudioTracks.size(); i++)
        {
            String name = savedAudioTracks[i].title;
            String text = searchTextEditor.getText();
            bool found = name.contains(text);
            if (found)
            {
                foundAudioTracks.push_back(savedAudioTracks[i]);
            }
        }
        
        displayAudioTracks(foundAudioTracks);
    }
    
}

// Search: Restore playlist items
void PlaylistComponent::searchTextEditorRestore()
{
    std::cout << "search text removed " << searchTextEditor.getText() << std::endl;
    if (searchTextEditor.getText().length() == 0)
    {
        // show original list of audio tracks
        displayAudioTracks(savedAudioTracks);
    }
    
}

// Calculate number of rows in playlist
int PlaylistComponent::getNumRows()
{
    return audioTracks.size();
}

// Change playlist background
void PlaylistComponent::paintRowBackground (Graphics & g,
                         int row,
                         int width,
                         int height,
                         bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange); // selected row colour
    }
    else
    {
        g.fillAll(Colours::dimgrey); // default row colour
    }
}

// Render cell content
void PlaylistComponent::paintCell (Graphics & g,
                int rowNumber,
                int columnId,
                int width,
                int height,
                bool rowIsSelected)
{
    // add text content to column 1: file names
    if (columnId == 1)
    {
        g.drawText(audioTracks[rowNumber].title,
                   2,
                   0,
                   width - 4,
                   height,
                   Justification::centredLeft,
                   true);
    }
    // add text content to column 2: track duration
    if (columnId == 2)
    {
        g.drawText(std::to_string(audioTracks[rowNumber].lengthInSec) + " sec",
                   2,
                   0,
                   width - 4,
                   height,
                   Justification::centredLeft,
                   true);
    }
}

// add buttons to columns 3, 4 and 5
Component* PlaylistComponent::refreshComponentForCell (int rowNumber,
                                    int columnId,
                                    bool isRowSelected,
                                    Component *existingComponentToUpdate)
{
    // add side1Btn for each row from audioTracks vector
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            std::cout << "refresh cell component " << rowNumber << " - " << audioTracks[rowNumber].name << std::endl;
            existingComponentToUpdate = audioTracks[rowNumber].side1Btn;
            existingComponentToUpdate->setColour(TextButton::buttonColourId, Colours::darkorange);

        }
    }
    // add side2Btn for each row from audioTracks vector
    if (columnId == 4)
    {
        if (existingComponentToUpdate == nullptr)
        {
            existingComponentToUpdate = audioTracks[rowNumber].side2Btn;
            existingComponentToUpdate->setColour(TextButton::buttonColourId, Colours::darkorange);

        }
    }
    // add removeBtn for each row from audioTracks vector
    if (columnId == 5)
    {
        if (existingComponentToUpdate == nullptr)
        {
            existingComponentToUpdate = audioTracks[rowNumber].removeBtn;
            existingComponentToUpdate->setColour(TextButton::buttonColourId, Colours::dimgrey);
            existingComponentToUpdate->addMouseListener(this, true);

        }
    }
    return existingComponentToUpdate;
}

// Button click callback
void PlaylistComponent::buttonClicked(Button* button)
{
    // Load button
    if (button == &loadButton)
    {
        std::cout << "LoadButton::buttonClicked" <<  std::endl;
        loadPlaylistDirectory();
    }
    // Remove All button
    if (button == &removeAllButton)
    {
        std::cout << "RemoveAllButton::buttonClicked" <<  std::endl;
        savedAudioTracks.clear();
        displayAudioTracks(savedAudioTracks);
        
    }
    else
    {
        // Check buttons in table cells
        for (int idx = 0; idx < audioTracks.size(); idx++)
        {
            // Side 1 button
            if (audioTracks[idx].side1Btn == button)
            {
                // index in playlist found, side 1
                selectedAudioTrackIndex = idx;
                selectedSide = 1;
                
                sendChangeMessage();
                return;
            }
            // Side 2 button
            else if (audioTracks[idx].side2Btn == button)
            {
                // index in playlist found, side 2
                selectedAudioTrackIndex = idx;
                selectedSide = 2;
                // send change message to DeckGUI
                sendChangeMessage();
                return;
            }
            // Remove button
            else if (audioTracks[idx].removeBtn == button)
            {
                std::vector<AudioTrack> foundAudioTracks;
                
                for (int i = 0; i < audioTracks.size(); i++)
                {
                    if (audioTracks[i].url != audioTracks[idx].url)
                    {
                        foundAudioTracks.push_back(audioTracks[i]);
                    }
                }
                displayAudioTracks(foundAudioTracks);
                return;
            }
        }
    }
}

// cellClicked event callback
void PlaylistComponent::cellClicked (int rowNumber, int columnId, const MouseEvent& e)
{
    // Send selected track to Deck 1
    selectedSide = 1;
    selectedAudioTrackIndex = rowNumber;
    sendChangeMessage();
}

// Load audio files to playlist
void PlaylistComponent::loadPlaylistDirectory()
{
    FileChooser chooser{"Select a directory for a playlist..."};
    if (chooser.browseForMultipleFilesToOpen())
    {
        savedAudioTracks.clear();

        // Get selected files
        std::cout << "results: " << std::endl;
        Array<File> audioFiles = chooser.getResults();
        // For each selected file
        for (File& audiFile : audioFiles) {
            // Create AudioTrack object
            AudioTrack track;
            track.name = audiFile.getFileName().toStdString();
            track.url = URL{audiFile};
            
            // Add title
            unsigned long pos = track.name.find(".");
            std::string title = track.name.substr(0, pos);
            track.title = title;
    
            // Get length in seconds
            track.lengthInSec = DJAudioPlayer::getAudioLengthInSeconds(track.url);
            
            std::cout << "Track " << track.name << " lenght: " << track.lengthInSec << std::endl;
            
            savedPlaylist.appendText(track.name + ";");
            
            // Add to audioTracks vector
            savedAudioTracks.push_back(track);
        }
        
        displayAudioTracks(savedAudioTracks);
    }
}

void PlaylistComponent::displayAudioTracks(std::vector<AudioTrack> newAudioTracks)
{
    audioTracks.clear();
    
    tableComponent.updateContent();
    tableComponent.repaint();
    
    for (int i = 0; i < newAudioTracks.size(); i++) {
        audioTracks.push_back(newAudioTracks[i]);
        unsigned long last = audioTracks.size() - 1;
        
        audioTracks[last].side1Btn = new TextButton{"Side 1"};
        audioTracks[last].side1Btn->addListener(this);
        
        audioTracks[last].side2Btn = new TextButton{"Side 2"};
        audioTracks[last].side2Btn->addListener(this);
        
        audioTracks[last].removeBtn = new TextButton{"Remove"};
        audioTracks[last].removeBtn->addListener(this);
    }
    
    // Update and rerender table
    tableComponent.updateContent();
    tableComponent.repaint();
}

void PlaylistComponent::loadSavedPlaylist()
{
    
}

void PlaylistComponent::readPlaylist(const juce::File& fileToRead)
{
    if (! fileToRead.existsAsFile())
    {
        std::cout << "file does not exist" << std::endl;
        return;
    }
     
    auto fileText = fileToRead.loadFileAsString();
    
}

// Return selected audio track
AudioTrack PlaylistComponent::getSelectedAudioTrack()
{
    return audioTracks[selectedAudioTrackIndex];
}

// Return selected side
int PlaylistComponent::getSelectedSide()
{
    return selectedSide;
}
