#pragma once
#include <iostream>
#include <string>

enum class Genre
{
    Vietnamese,
    Western,
    KPop,
    Japanese,
    Chinese,
};

class Platform;

class Song
{
    std::string title;
    std::string artist;
    std::string lyrics;
    Genre genre;
    int releaseYear;
    int currentPlayCount;

    friend class Platform; 

public:
    Song(const std::string& path);
    Song(const std::string& title, const std::string& artist, const std::string& lyrics, Genre genre, int releaseYear)
        : title(title), artist(artist), lyrics(lyrics), genre(genre), releaseYear(releaseYear), currentPlayCount(0) {}  

    ~Song();
    
    const std::string& getTitle() const { return title; }
    const std::string& getArtist() const { return artist; }
    const std::string& getLyrics() const { return lyrics; }
    int getReleaseYear() const { return releaseYear; }
    
    friend std::ostream& operator<<(std::ostream& os, const Song& song);

	int getCurrentPlayCount() const { return currentPlayCount; }

    void load(const std::string& path);
    void save(const std::string& path) const;
private:
};
