#include "DungGiua.h"

void DungGiua::registerPlatform(const std::string& name)
{
	if (name.empty())
	{
		throw std::invalid_argument("Platform name cannot be empty.");
	}
	if (platforms.find(name) != platforms.end())
	{
		throw std::runtime_error("Platform already exists: " + name);
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

const Platform* DungGiua::getPlatform(const std::string& name) const
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
		throw std::invalid_argument("Cannot add a null song.");
	}
	Platform* platform = platforms[platformName];
	if (platform->excludeArtists.find(song->getArtist()) != platform->excludeArtists.end())
	{
		throw std::runtime_error("Artist is exclusive to another platform: " + song->getArtist());
	}
	platform->addSong(song);
}