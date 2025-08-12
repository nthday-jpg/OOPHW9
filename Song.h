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
protected:
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

    virtual Genre getGenre() const { return genre; }
    virtual const std::string& getTitle() const { return title; }
    virtual const std::string& getArtist() const { return artist; }
    virtual const std::string& getLyrics() const { return lyrics; }
    virtual int getReleaseYear() const { return releaseYear; }
    
    friend std::ostream& operator<<(std::ostream& os, const Song& song);

    virtual int getCurrentPlayCount() const { return currentPlayCount; }

    virtual void load(const std::string& path);
    virtual void save(const std::string& path) const;
private:
};

class CopyrightedSong : public Song
{
    int fee;
public:
    CopyrightedSong(const std::string& title, const std::string& artist, const std::string& lyrics, Genre genre, int releaseYear, int fee)
        : Song(title, artist, lyrics, genre, releaseYear), fee(fee) {
    }

};