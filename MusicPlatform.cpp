#include "MusicPlatform.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;

Platform::Platform(const std::string& name, const std::string& path_to_songs) :
	path_to_songs(path_to_songs), name(name)
{
    loadSongs();
}

Platform::~Platform()
{
	ofstream outFile(path_to_songs);
    if (!outFile.is_open())
    {
        throw std::runtime_error("Could not open file: " + path_to_songs);
	}
    if (!std::filesystem::exists("musics"))
    {
        std::filesystem::create_directory("musics");
	}

    for (auto& pair : songs)
    {
        std::filesystem::path savePath = std::filesystem::path("musics") / (pair.second->getTitle() + ".txt");
		outFile << pair.second->getTitle() << "," << savePath.generic_string() << "\n";
        pair.second->save(savePath.string());
        delete pair.second;
    }
    songs.clear();
}

void Platform::loadSongs()
{
    ifstream songFile(path_to_songs);
    string line;

    while (getline(songFile, line))
    {
        // Line format: title, path
        istringstream iss(line);
        string title, path;
        getline(iss, title, ',');
        getline(iss, path, ',');

        Song* song = new Song(path);
        addSong(song);
    }
}

void Platform::addSong(Song* song)
{
    if (song == nullptr)
    {
        cout << "Cannot add a null song." << endl;
        return;
    }
    if (songs.find(song->getTitle()) != songs.end())
    {
        cout << "Song already exists: " << song->getTitle() << endl;
        return;
	}
    songs[song->getTitle()] = song;
}

void Platform::removeSong(const std::string& user, const std::string& title)
{
    if (songs.find(title) == songs.end())
    {
        cout << "Song not found: " << title << endl;
        return;
	}
    if (songs[title]->getArtist() != user)
    {
        cout << "You are not authorized to remove this song." << endl;
        return;
    }
    delete songs[title];
    songs.erase(title);
}

Song* Platform::getSong(const std::string& title) const
{
    auto it = songs.find(title);
    if (it != songs.end()) {
        return it->second;
    }
    return nullptr;  
}

void Platform::displayAllSongs() const
{
    if (songs.empty())
    {
        cout << "No songs available." << endl;
        return;
    }
    cout << "Available songs:" << endl;
    for (const auto& pair : songs)
    {
        cout << pair.second->getTitle() << " by " << pair.second->getArtist() << endl;
    }
}

void Platform::increasePlayCount(Song* song)
{
    if (song == nullptr)
    {
        cout << "Cannot increase play count for a null song." << endl;
        return;
    }
	song->currentPlayCount++;
}

std::vector<Song*> Platform::getTop5MostPlayedSongs() const
{
    std::vector<Song*> allSongs;
    
    // Collect all songs from the map
    for (const auto& pair : songs)
    {
        allSongs.push_back(pair.second);
    }
    
    // Sort by play count in descending order
    std::sort(allSongs.begin(), allSongs.end(), 
              [](const Song* a, const Song* b) {
                  return a->currentPlayCount > b->currentPlayCount;
              });
    
    // Return top 5 (or fewer if there are less than 5 songs)
    std::vector<Song*> top5;
    int count = std::min(5, static_cast<int>(allSongs.size()));
    
    for (int i = 0; i < count; ++i)
    {
        top5.push_back(allSongs[i]);
    }
    
    return top5;
}