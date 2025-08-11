#pragma once
#include <iostream>
#include <string>  
#include <unordered_map> 
#include <set>
#include "Song.h"

class Platform
{
	std::string name;
    std::unordered_map<std::string, Song*> songs; 
    std::set<std::string> excludeArtists;
    std::string path_to_songs;

	friend class DungGiua; 
public:
    Platform(const std::string&name, const std::string& path_to_songs);
    ~Platform();

	std::string getName() const { return name; }

    void addSong(Song* song);
    void removeSong(const std::string& user, const std::string& title);
    void displayAllSongs() const;
    const Song* getSong(const std::string& title) const;

private:
    void loadSongs();
};