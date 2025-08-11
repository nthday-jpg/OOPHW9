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

void Playlist::setName(const std::string& newName)
{
	if (newName.empty())
	{
		std::cout << "Playlist name cannot be empty." << std::endl;
		return;
	}
	name = newName;
}

void Playlist::addSong(const Song* song)
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

}

void Playlist::playSong() 
{
	if (songs.empty())
	{
		std::cout << "No songs in the playlist." << std::endl;
		return;
	}
	const Song* currentSong = songs[currentSongIndex];
	std::cout << "Playing: " << currentSong->getTitle() << " by " << currentSong->getArtist() << std::endl;
}

void Playlist::stopSong()
{
	if (songs.empty())
	{
		std::cout << "No songs in the playlist." << std::endl;
		return;
	}
	const Song* currentSong = songs[currentSongIndex];
	std::cout << "Stopped: " << currentSong->getTitle() << " by " << currentSong->getArtist() << std::endl;
}