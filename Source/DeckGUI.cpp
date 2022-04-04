/*
  ==============================================================================

    DeckGUI.cpp
    Created: 23 Feb 2022
    Author:  Alina Uzhvieva

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(int _sideNumber,
                 DJAudioPlayer* _player,
                 PlaylistComponent* _playlistComponent,
                 AudioFormatManager & 	formatManagerToUse,
                 AudioThumbnailCache & 	cacheToUse
           ) : sideNumber(_sideNumber),
               player(_player),
               playlistComponent(_playlistComponent),
               waveformDisplay(formatManagerToUse, cacheToUse)
               
{
    playlistComponent->addChangeListener(this);
        
    /* Rendering elements in UI */
    addAndMakeVisible(playButton);
    addAndMakeVisible(againButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(prevButton);
    addAndMakeVisible(loopButton);
    addAndMakeVisible(nextButton);
    
    // Disable some buttons that don't work yet
    prevButton.setEnabled(false);
    nextButton.setEnabled(false);
    loopButton.setEnabled(false);
    loopButton.setToggleable(true);
    
    // Render slider
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    
    // Setting slider style
    volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    speedSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    posSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    
    // Slider label position
    volSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    posSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    
    // Add suffix to value
    volSlider.setTextValueSuffix("%");
    speedSlider.setTextValueSuffix("x");
    posSlider.setTextValueSuffix("s");
    
    // More UI customizations
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::orange);
    
    // Render Waveform Display
    addAndMakeVisible(waveformDisplay);

    /* Event listeners */
    playButton.addListener(this);
    stopButton.addListener(this);
    prevButton.addListener(this);
    nextButton.addListener(this);
    againButton.addListener(this);
    loopButton.addListener(this);
    
    // Button images
    playButton.setImages(false, true, true,
                             ImageCache::getFromMemory(BinaryData::play_png,
                                                       BinaryData::play_pngSize),
                             0.5f, Colour(0xffe9692c),
                             ImageCache::getFromMemory(BinaryData::play_png,
                                                       BinaryData::play_pngSize),
                             0.5f, Colour(0xffffa500),
                             ImageCache::getFromMemory(BinaryData::play_png,
                                                       BinaryData::play_pngSize),
                             0.5f, Colours::darkorange);
    
    stopButton.setImages(false, true, true,
                             ImageCache::getFromMemory(BinaryData::pause_png,
                                                       BinaryData::pause_pngSize),
                             0.5f, Colour(0xffe9692c),
                             ImageCache::getFromMemory(BinaryData::pause_png,
                                                       BinaryData::pause_pngSize),
                             0.5f, Colour(0xffffa500),
                             ImageCache::getFromMemory(BinaryData::pause_png,
                                                       BinaryData::pause_pngSize),
                             0.5f, Colours::darkorange);
    
    againButton.setImages(false, true, true,
                             ImageCache::getFromMemory(BinaryData::again_png,
                                                       BinaryData::again_pngSize),
                             0.5f, Colour(0xffe9692c),
                             ImageCache::getFromMemory(BinaryData::again_png,
                                                       BinaryData::again_pngSize),
                             0.5f, Colour(0xffffa500),
                             ImageCache::getFromMemory(BinaryData::again_png,
                                                       BinaryData::again_pngSize),
                             0.5f, Colours::darkorange);
    
    prevButton.setImages(false, true, true,
                             ImageCache::getFromMemory(BinaryData::prev_png,
                                                       BinaryData::prev_pngSize),
                             0.5f, Colours::dimgrey,
                             ImageCache::getFromMemory(BinaryData::prev_png,
                                                       BinaryData::prev_pngSize),
                             0.5f, Colour(0xffffa500),
                             ImageCache::getFromMemory(BinaryData::prev_png,
                                                       BinaryData::prev_pngSize),
                             0.5f, Colours::darkorange);
    
    nextButton.setImages(false, true, true,
                             ImageCache::getFromMemory(BinaryData::next_png,
                                                       BinaryData::next_pngSize),
                             0.5f, Colours::dimgrey,
                             ImageCache::getFromMemory(BinaryData::next_png,
                                                       BinaryData::next_pngSize),
                             0.5f, Colour(0xffffa500),
                             ImageCache::getFromMemory(BinaryData::next_png,
                                                       BinaryData::next_pngSize),
                             0.5f, Colours::darkorange);
    
    loopButton.setImages(false, true, true,
                             ImageCache::getFromMemory(BinaryData::loop_png,
                                                       BinaryData::loop_pngSize),
                             0.5f, Colours::dimgrey,
                             ImageCache::getFromMemory(BinaryData::loop_png,
                                                       BinaryData::loop_pngSize),
                             0.5f, Colour(0xffffa500),
                             ImageCache::getFromMemory(BinaryData::loop_png,
                                                       BinaryData::loop_pngSize),
                             0.5f, Colours::darkorange);

    // Slider listeners
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    /* Setting range for sliders */
    volSlider.setRange(0.0, 100.0);
    speedSlider.setRange(0.0, 3.0); // careful here, 3 is more than enough
    posSlider.setRange(0.0, 100.0);
    
    // Setting precision to display
    volSlider.setNumDecimalPlacesToDisplay(0);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    posSlider.setNumDecimalPlacesToDisplay(2);
    
    // Setting slider default values
    volSlider.setValue(50.0);
    speedSlider.setValue(player->getCurrentSpeed());

    startTimer(500);

}

// Destructor
DeckGUI::~DeckGUI()
{
    stopTimer();
}

// Graphical Interface
void DeckGUI::paint (Graphics& g)
{
    g.fillAll (Colours::purple);   // clear the background
    
    // Header
    g.setColour (Colours::orange);
    g.setFont (16.0f);
    g.drawText ("Track Title:", 20, 20, getWidth(), getHeight(),
                Justification::top, true);
    // track name in header
    g.setColour (Colours::beige);
    g.drawText (currentTrackName, 100, 20, getWidth(), getHeight(),
               Justification::top, true);

    g.setColour (Colours::orange);
    g.setFont (14.0f);
    g.drawText ("", getLocalBounds(), Justification::centred, true);
    
    // Slider names
    g.drawText ("Volume", 0, getHeight()/8, getWidth() / 3, getHeight()*3/8,
                Justification::centred, true);
    g.drawText ("Speed", getWidth() / 3, getHeight()/8, getWidth() / 3, getHeight()*3/8,
                Justification::centred, true);
    g.drawText ("Position", getWidth()*2 / 3, getHeight()/8, getWidth() / 3, getHeight()*3/8,
                Justification::centred, true);
    
}

// Elements' position on canvas
void DeckGUI::resized()
{
    double rowH = getHeight() / 8;
    double colW = getWidth() / 6;
    double buttonH = rowH - 15;
    double buttonW = colW - 5;
    
    int dialWidth = getWidth() / 3;
    int dialHeight = rowH * 3;
    
    // Button positioning
    prevButton.setBounds(2, rowH * 4+10, buttonW, buttonH);
    againButton.setBounds(colW+2, rowH * 4+10, buttonW, buttonH);
    playButton.setBounds(colW*2+2, rowH * 4+10, buttonW, buttonH);
    stopButton.setBounds(colW*3+2, rowH * 4+10, buttonW, buttonH);
    loopButton.setBounds(colW*4+2, rowH * 4+10, buttonW, buttonH);
    nextButton.setBounds(colW*5+2, rowH * 4+10, buttonW, buttonH);
    
    // Slider positioning
    volSlider.setBounds(0, rowH , dialWidth, dialHeight);
    speedSlider.setBounds(dialWidth, rowH, dialWidth, dialHeight);
    posSlider.setBounds(dialWidth * 2, rowH, dialWidth, dialHeight);
    
    // Waveform Display
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);

}

// Event listener - button click
void DeckGUI::buttonClicked(Button* button)
{
    // Play Button
    if (button == &playButton)
    {
        player->start(); // start playback
    }
    // Stop button
    if (button == &stopButton)
    {
        player->stop(); // stop playback
    }
    if (button == &againButton)
    {
        // start over
        posSlider.setValue(0.0);
        player->setPosition(0.0);
    }
}

// Event listener - slider value change
void DeckGUI::sliderValueChanged (Slider *slider)
{
    // volume
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue()/100); // normalized value
    }

    // playback speed
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    // playback position
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue()/currentTrackLength); // normalized value
    }
}

// File drag listener
bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
    return true;
}

// When file is dropped inside player
void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        player->loadURL(URL{File{files[0]}});
    }
}

// Set waveform display position
void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}

// Playlist Listener
void DeckGUI::changeListenerCallback (ChangeBroadcaster* source)
{
    // check if this deck (side) is selected
    if (sideNumber == playlistComponent->getSelectedSide())
    {
        // get selected audio track
        AudioTrack selectedAudioTrack = playlistComponent->getSelectedAudioTrack();
        std::cout << "DeckGUI::changeListenerCallback: " << selectedAudioTrack.name << std::endl;
        
        // get information about this track
        currentTrackName = selectedAudioTrack.name; // goes to header
        currentTrackLength = selectedAudioTrack.lengthInSec; // goes to position slider
        
        // adjust position slider settings
        posSlider.setRange(0.0, currentTrackLength);
        posSlider.setNumDecimalPlacesToDisplay(2);
        posSlider.setValue(0.0);
        
        // rerender GUI
        repaint();
        
        // load selected audio file
        player->loadURL(selectedAudioTrack.url);
        waveformDisplay.loadURL(selectedAudioTrack.url);
    }
}
