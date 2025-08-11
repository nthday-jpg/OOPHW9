#pragma once
#include <iostream>
#include <string>  
#include <unordered_map> 
#include <set>
#include "Song.h"

class Platform
{
    std::unordered_map<std::string, Song*> songs; 
    std::set<std::string> excludeArtists;
    std::string path_to_songs;
public:
    Platform(const std::string& path_to_songs);
    ~Platform();

    void addSong(Song* song);
    const Song* getSong(const std::string& title) const;
    void removeSong(const std::string& user, const std::string& title);
private:
    void loadSongs();
};