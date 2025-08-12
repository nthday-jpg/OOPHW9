#include "DungGiua.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

DungGiua::~DungGiua()
{
	savePlatforms(); 
	for (auto& pair : platforms)
	{
		delete pair.second;
	}
	platforms.clear();
}

void DungGiua::registerPlatform(const std::string& name)
{
	if (name.empty())
	{
		throw std::invalid_argument("Platform name cannot be empty.");
	}
	if (platforms.find(name) != platforms.end())
	{
		std::cout << "Platform already exists: " << name << std::endl;
		return;
	}
	Platform* newPlatform = new Platform(name, "musics/" + name + ".txt");
	platforms[name] = newPlatform;
}

void DungGiua::removePlatform(const std::string& name)
{
	auto it = platforms.find(name);
	if (it != platforms.end())
	{
		delete it->second;
		platforms.erase(it);
	}
	else
	{
		throw std::runtime_error("Platform not found: " + name);
	}
}

Platform* DungGiua::getPlatform(const std::string& name) const
{
	auto it = platforms.find(name);
	if (it != platforms.end())
	{
		return it->second;
	}
	return nullptr;
}

std::string DungGiua::exclusiveArtist(const std::string& artist)
{
	for (const auto& pair : platforms)
	{
		const Platform* platform = pair.second;
		if (platform->excludeArtists.find(artist) != platform->excludeArtists.end())
		{
			return pair.first; 
		}
	}
	return ""; 
}

void DungGiua::addSongToPlatform(const std::string& platformName, Song* song)
{
	// check if the artist is exclusive to the platform
	if (platforms.find(platformName) == platforms.end())
	{
		throw std::runtime_error("Platform not found: " + platformName);
	}
	if (song == nullptr)
	{
		throw std::invalid_argument("Cannot a null song.");
	}
	Platform* platform = platforms[platformName];
	if (platform->excludeArtists.find(song->getArtist()) != platform->excludeArtists.end())
	{
		throw std::runtime_error("Artist is exclusive to another platform: " + song->getArtist());
	}
	platform->addSong(song);
}

// File format: name,path_to_songs
void DungGiua::loadPlatforms()
{
	std::ifstream file("assets/platforms.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open platforms file.");
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string name, path_to_songs;
		if (std::getline(iss, name, ',') && std::getline(iss, path_to_songs))
		{
			if (name.empty())
			{
				throw std::invalid_argument("Platform name cannot be empty.");
			}
			if (platforms.find(name) != platforms.end())
			{
				throw std::runtime_error("Platform already exists: " + name);
			}
			Platform* newPlatform = new Platform(name, path_to_songs);
			platforms[name] = newPlatform;
			newPlatform->loadSongs();
		}
		else
		{
			throw std::runtime_error("Invalid platform format: " + line);
		}
	}
}

void DungGiua::savePlatforms()
{
	std::ofstream file("assets/platforms.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open platforms file for saving.");
	}
	for (const auto& pair : platforms)
	{
		const Platform* platform = pair.second;
		file << platform->getName() << "," << platform->path_to_songs << "\n";
	}
	file.close();
}