# OtoDecks Application

## Overview

**OtoDecks** is an audio mixing application developed as part of an Object-Oriented Programming coursework. The application allows users to load, play, and mix audio tracks, simulating a basic DJ setup with two decks. The project was designed to implement and demonstrate various OOP principles and features using the JUCE framework.

## Features

- **Load and Play Audio Files**: Users can load audio files into either of the two decks and play them simultaneously.
- **Mixing Tracks**: Independent volume control for each deck allows users to mix tracks by adjusting their volumes.
- **Speed Control**: Users can speed up or slow down the playback of each track independently.
- **Custom Deck Controls**: The application includes custom controls for playback, allowing users to restart tracks and manage playback positions.
- **Music Library Management**: A music library component enables users to manage their audio files, including adding, removing, and searching for tracks.

## Challenges and Solutions

### Custom UI Development
- **Challenge**: Implementing custom graphics and controls for the application while maintaining a user-friendly interface.
- **Solution**: Developed custom components using JUCE's ImageButton and Slider components, and applied custom styling to match the desired aesthetics.

### Team Member Absences
- **Challenge**: The project faced challenges with team member participation, which required a redistribution of responsibilities.
- **Solution**: Adapted the project plan and took on additional roles to ensure the project was completed on time, managing both backend and frontend tasks.

### Technical Challenges
- **Challenge**: Integrating audio playback functionality and managing the state across multiple components.
- **Solution**: Utilized JUCE's DJAudioPlayer class and custom message handling to ensure smooth interaction between the playlist, deck components, and audio playback.

## Installation and Setup

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/otodecks.git
   ```
2. **Open in IDE**: Open the project in an IDE that supports JUCE, such as Xcode or Visual Studio.
3. **Build the Project**: Compile the project within the IDE.
4. **Run the Application**: Once built, you can run the application directly from the IDE.

## Usage

1. **Loading Tracks**: Click on "Add to Playlist" to load audio files. Use the "Side 1" and "Side 2" buttons to assign tracks to the respective decks.
2. **Playing Tracks**: Use the play button on each deck to start playback. The tracks can be played simultaneously.
3. **Mixing**: Adjust the volume sliders on each deck to mix the tracks. The speed slider can be used to change the playback speed.
4. **Custom Controls**: Use custom buttons to restart tracks or adjust playback positions.

## Code Structure

- **PlaylistComponent**: Manages the music library and allows users to load tracks into the decks.
- **DeckGUI**: Handles the user interface for each deck, including playback controls, volume, and speed sliders.
- **DJAudioPlayer**: Manages audio playback, including loading, playing, and adjusting tracks.

## Future Enhancements

- **Persistent Music Library**: Implement a feature to save the music library state so that it persists between sessions.
- **Advanced Mixing Features**: Add more advanced audio effects and mixing capabilities.
- **Improved UI**: Further refine the user interface for better usability and aesthetics.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
