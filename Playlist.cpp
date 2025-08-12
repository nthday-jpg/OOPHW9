#include "Playlist.h"

Playlist::Playlist(const std::string& name) : name(name), currentSongIndex(0)
{
    if (name.empty())
    {
        std::cout << "Playlist name cannot be empty." << std::endl;
    }
}

Playlist::~Playlist()
{
    
}

void Playlist::displaySongs() const
{
    if (songs.empty())
    {
        std::cout << "No songs in the playlist." << std::endl;
        return;
    }
    std::cout << "Songs in playlist '" << name << "':" << std::endl;
    for (size_t i = 0; i < songs.size(); ++i)
    {
        std::cout << i + 1 << ". " << songs[i]->getTitle() << " by " 
                  << songs[i]->getArtist() << " (Play count: " 
                  << songs[i]->getCurrentPlayCount() << ")" << std::endl;
    }
}

void Playlist::setName(const std::string& newName)
{
    if (newName.empty())
    {
        std::cout << "Playlist name cannot be empty." << std::endl;
        return;
    }
    name = newName;
}

void Playlist::addSong(Song* song)  // Remove const
{
    if (song == nullptr)
    {
        std::cout << "Cannot add a null song." << std::endl;
        return;
    }
    songs.push_back(song);
}

void Playlist::nextSong() 
{
    if (songs.empty())
    {
        std::cout << "No songs in the playlist." << std::endl;
        return;
    }
    currentSongIndex = (currentSongIndex + 1) % songs.size();
    playSong();
}

void Playlist::previousSong() 
{
    if (songs.empty())
    {
        std::cout << "No songs in the playlist." << std::endl;
        return;
    }
    currentSongIndex = (currentSongIndex - 1 + songs.size()) % songs.size();
    playSong();
}

void Playlist::removeSong()
{
    if (songs.empty())
    {
        std::cout << "No songs in the playlist." << std::endl;
        return;
    }
    songs.erase(songs.begin() + currentSongIndex);
    if (currentSongIndex >= songs.size() && !songs.empty())
    {
        currentSongIndex = 0;
    }
}

void Playlist::playSong() 
{
    if (songs.empty())
    {
        std::cout << "No songs in the playlist." << std::endl;
        return;
    }
    Song* currentSong = songs[currentSongIndex];  // Remove const
        
    std::cout << "Playing: " << currentSong->getTitle() << " by " << currentSong->getArtist() 
              << " (Play count: " << currentSong->getCurrentPlayCount() << ")" << std::endl;
}

void Playlist::stopSong()
{
    if (songs.empty())
    {
        std::cout << "No songs in the playlist." << std::endl;
        return;
    }
    Song* currentSong = songs[currentSongIndex];  // Remove const
    std::cout << "Stopped: " << currentSong->getTitle() << " by " << currentSong->getArtist() << std::endl;
}