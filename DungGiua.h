#pragma once
#include <unordered_map>
#include "MusicPlatform.h"
// This class is used to manage platforms

class DungGiua
{
	std::unordered_map<std::string, Platform*> platforms; 
public:
	~DungGiua();
	void registerPlatform(const std::string& name);
	void removePlatform(const std::string& name);
	Platform* getPlatform(const std::string& name) const;
	
	void addSongToPlatform(const std::string& platformName, Song* song);

private:
	// get the platform if the artist is exclusive to the platform
	std::string exclusiveArtist(const std::string& artist);
	void loadPlatforms();
	void savePlatforms();
};