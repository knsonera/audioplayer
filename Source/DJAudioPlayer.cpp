/*
==============================================================================

DJAudioPlayer.cpp
Created: 23 Feb 2022
Author:  Alina Uzhvieva

==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager) 
: formatManager(_formatManager)
{}

DJAudioPlayer::~DJAudioPlayer()
{}

// AudioSource methods
void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) 
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

// Load URL and set audio transport source
void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {       
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);             
        readerSource.reset (newSource.release());          
    }
}

// Set audio volume
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
   
}

// Set audio speed
void DJAudioPlayer::setSpeed(double ratio)
{
  if (ratio < 0 || ratio > 5.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 5" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}

// Set audio position
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

// Set relative position (when it's not in seconds)
void DJAudioPlayer::setPositionRelative(double pos)
{
     if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

// start playback
void DJAudioPlayer::start()
{
    transportSource.start();
}

// stop playback
void DJAudioPlayer::stop()
{
    transportSource.stop();
}

// get current position
double DJAudioPlayer::getPosition()
{
    return transportSource.getCurrentPosition();
}

// get relative position for waveform display
double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

// get track length in seconds
double DJAudioPlayer::getTrackLength()
{
    return transportSource.getLengthInSeconds();
}

// get current volume
double DJAudioPlayer::getCurrentVol()
{
    return transportSource.getGain();
}

// get current speed
double DJAudioPlayer::getCurrentSpeed()
{
    return resampleSource.getResamplingRatio();
}
