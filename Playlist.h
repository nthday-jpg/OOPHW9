#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include "Song.h"

class Playlist
{
	std::string name; 
    std::vector<const Song*> songs; 
    int currentSongIndex = 0;
	friend class App; 
public:
    Playlist(const std::string& name);
	~Playlist();

    void setName(const std::string& newName);

	void addSong(const Song* song);
    void nextSong();
    void previousSong();
	void removeSong(); // Remove the current song from the playlist
    void playSong();
    void stopSong();
};
