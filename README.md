Here’s a sample `README.md` for your music player project:

---

# C++ Music Player 🎶

A terminal-based music player in C++ using [SFML](https://www.sfml-dev.org/) for audio handling and circular doubly linked lists for playlist management. This music player allows users to play, pause, shuffle, and traverse through songs. Users can also specify the playback order for a customized playlist experience. The music player employs multi-threading and similar concepts to ensure smooth and seamless playback on the go!

## Features

- **Play/Pause**: Toggle playback of the current song.
- **Next/Previous**: Navigate between songs in the playlist.
- **Shuffle**: Randomize the order of songs in the playlist.
- **Select Specific Song**: Search and play a specific song by name.
- **Custom Order Playback**: Specify a custom order for songs to be played.
- **Autoplay**: Automatically transition to the next song when the current song finishes.

## Prerequisites

- **C++17 or higher**: Ensure your compiler supports C++17.
- **SFML Library**: Install SFML for audio handling.

  ```bash
  # On Ubuntu
  sudo apt update
  sudo apt install libsfml-dev
  ```

## Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/yourusername/music-player
   cd music-player
   ```

2. **Compile the code**:

   ```bash
   g++ -std=c++17 -o music_player main.cpp -lsfml-audio -lsfml-system -lpthread
   ```

3. **Add your music**: Place `.mp3` files in the `music` folder at the root of the project directory.

## Usage

Run the executable from the terminal:

```bash
./music_player
```

### Commands

Upon running the program, you’ll see the following options:

1. **Play Next Song**: Skip to the next song in the playlist.
2. **Play Previous Song**: Return to the previous song.
3. **Show Playlist**: Display the songs available in the playlist.
4. **Shuffle Playlist**: Randomly reorder the songs in the playlist.
5. **Pause/Resume**: Pause or resume the currently playing song.
6. **Play Specific Song**: Search for a song by name and play it.
7. **Exit**: Close the program.

### Setting Custom Order

When prompted, you can enter a sequence of numbers corresponding to the indices of songs displayed in the playlist. Invalid inputs or non-existing indices will be ignored.

## Example

Sample directory structure:

```plaintext
music-player/
├── main.cpp
├── music/
│   ├── song1.mp3
│   ├── song2.mp3
│   └── song3.mp3
└── README.md
```

## Error Handling

- **File Not Found**: Displays an error if a specified `.mp3` file is not found.
- **Invalid Input**: Ignores invalid song indices in the custom order input.
- **Empty Playlist**: Prompts the user if the playlist directory is empty or no `.mp3` files are found.

## Troubleshooting

If you encounter errors like linking issues or missing libraries, ensure SFML is installed properly and try compiling with additional flags as necessary (e.g., `-lstdc++`, `-lpthread`).

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to help improve the project.

---

This `README.md` provides a structured guide to help users understand the setup, usage, and troubleshooting for your project. Let me know if you'd like additional customization!
