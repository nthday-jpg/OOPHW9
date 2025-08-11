#include "Song.h"
#include <fstream>
#include <sstream>
#include <filesystem>

Song::Song(const std::string& path)
{
    load(path);
}

Song::~Song()
{
    std::filesystem::path savePath = std::filesystem::path("musics") / (title + ".txt");
    save(savePath.string());
}

void Song::save(const std::string& path) const
{
    std::ofstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + path);
    }
    file << title << "\n"
        << artist << "\n"
        << static_cast<int>(genre) << "\n"
        << releaseYear << "\n"
        << currentPlayCount << "\n"
        << lyrics << "\n";
    file.close();
}


void Song::load(const std::string& path) 
{
    std::ifstream file(path);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Could not open file: " + path);
    }
    std::string line;
    std::getline(file, title);
    std::getline(file, artist);
    int genreInt;
    file >> genreInt;
    genre = static_cast<Genre>(genreInt);
    file >> releaseYear;
    file >> currentPlayCount;
    file.ignore(); 
    std::getline(file, lyrics);
    file.close();
}

std::ostream& operator<<(std::ostream& os, const Song& song)
{
    os << "Title: " << song.title << "\n"
        << "Artist: " << song.artist << "\n"
        << "Genre: " << static_cast<int>(song.genre) << "\n"
        << "Release Year: " << song.releaseYear << "\n"
        << "Current Play Count: " << song.currentPlayCount;
    return os;
}