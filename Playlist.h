#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include "Song.h"

class Playlist
{
    std::string name; 
    std::vector<Song*> songs;  
    int currentSongIndex = 0;
    friend class App; 
public:
    Playlist(const std::string& name);
    ~Playlist();

	void displaySongs() const;
    void setName(const std::string& newName);
    void addSong(Song* song);  
    void nextSong();
    void previousSong();
    void removeSong();
    void playSong();
    void stopSong();
};
