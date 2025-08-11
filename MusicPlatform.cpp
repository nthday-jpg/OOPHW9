#include "MusicPlatform.h"
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

Platform::Platform(const std::string& path_to_songs) : path_to_songs(path_to_songs)
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

const Song* Platform::getSong(const std::string& title) const
{
    auto it = songs.find(title);
    if (it != songs.end()) {
        return it->second;
    }
    return nullptr;  
}