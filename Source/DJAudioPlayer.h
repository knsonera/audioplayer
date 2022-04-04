/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 23 Feb 2020
    Author:  Alina Uzhvieva

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public AudioSource {
  public:

    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    /* AudioSource methods: */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    /* load file from URL */
    void loadURL(URL audioURL);
    /* change sound volume */
    void setGain(double gain);
    /* change playback speed */
    void setSpeed(double ratio);
    /* change playback position */
    void setPosition(double posInSecs);
    /* change relative playback position inside GUI component */
    void setPositionRelative(double pos);
    
    /* start playback */
    void start();
    /* stop playback */
    void stop();

    /* get current playback position */
    double getPosition();
    double getPositionRelative();
    // get current track length
    double getTrackLength();
    // get current audio settings
    double getCurrentVol();
    double getCurrentSpeed();
    
    // static function to get length of each audio in playlist
    static double getAudioLengthInSeconds(URL audioFileUrl)
    {
        // settting up format manager, format reader source and audio transport source
        AudioFormatManager formatManager;
        formatManager.registerBasicFormats();
        
        std::unique_ptr<AudioFormatReaderSource> readerSource;
        AudioTransportSource transportSource;

        // creating reader
        auto* reader = formatManager.createReaderFor(audioFileUrl.createInputStream(false));
        if (reader != nullptr)
        {
            std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
            // set source for AudioTransportSource
            transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource.reset (newSource.release());
            // return length in seconds for audio file
            return transportSource.getLengthInSeconds();
        }
        else
        {
            return 0;
        }
    }

private:
    AudioDeviceManager deviceManager;
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource; 
    ResamplingAudioSource resampleSource{&transportSource, false, 2};

};




