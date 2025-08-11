#include "App.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

App::App() : curPlaylist(nullptr), 
			accountPath("assets/accounts.txt"),
			currentPlatform(nullptr), 
			accountManager(accountPath)
{
	
}

App::~App()
{
	logout(); 
	for (auto& pair : playlists)
	{
		delete pair.second;
	}
	playlists.clear();
}

void App::setPlatform(Platform* platform)
{
	currentPlatform = platform;
	cout << "Platform set successfully." << endl;
}

void App::addPlaylist(const string& name)
{
	if (name.empty())
	{
		cout << "Playlist name cannot be empty." << endl;
		return;
	}
	if (playlists.find(name) != playlists.end())
	{
		cout << "Playlist already exists: " << name << endl;
		return;
	}
	Playlist* newPlaylist = new Playlist(name);
	if (!curPlaylist)
	{
		curPlaylist = newPlaylist; 
	}
	playlists[name] = newPlaylist;
	cout << "Added playlist: " << name << endl;
}

Playlist* App::getPlaylistByName(const std::string& name)
{
    auto it = playlists.find(name);
    if (it != playlists.end()) {
        return it->second;
    }
    return nullptr;
}

void App::removePlaylist(const string& name)
{
    Playlist* playlist = getPlaylistByName(name);
    if (playlist)
    {
        if (curPlaylist == playlist) {
            curPlaylist = nullptr;
        }
        
        delete playlist;
        playlists.erase(name);
        cout << "Removed playlist: " << name << endl;
    }
    else
    {
        cout << "Playlist not found: " << name << endl;
    }
}

void App::setCurrentPlaylist(const string& name)
{
    Playlist* playlist = getPlaylistByName(name);
    if (playlist)
    {
        curPlaylist = playlist;
        cout << "Current playlist set to: " << name << endl;
    }
    else
    {
        cout << "Playlist not found: " << name << endl;
    }
}

void App::addSongToPlaylist(const string& playlistName, const string& title)
{
    Playlist* playlist = getPlaylistByName(playlistName);
    if (!playlist)
    {
        cout << "Playlist not found: " << playlistName << endl;
        return;
    }
    
    if (!currentPlatform)
    {
        cout << "No platform set. Please set a platform first." << endl;
        return;
    }
    
    const Song* song = currentPlatform->getSong(title);
    if (song)
    {
        playlist->addSong(song);  
        cout << "Added song: " << title << " to playlist: " << playlistName << endl;
    }
    else
    {
        cout << "Song not found: " << title << endl;
    }
}

void App::playNextSong()
{
	curPlaylist->nextSong();
}

void App::playPreviousSong()
{
	curPlaylist->previousSong();
}

void App::removeCurrentSong()
{
	curPlaylist->removeSong();
	cout << "Removed current song from the current playlist." << endl;
}

void App::playCurrentSong()
{
	curPlaylist->playSong();
}

void App::stopCurrentSong()
{
	curPlaylist->stopSong();
	cout << "Stopped current song." << endl;
}

void App::login(const string& username, const string& password)
{
	accountManager.login(username, password);
	loadPlaylists();
	if (playlists.empty())
	{
		curPlaylist = new Playlist("Default Playlist");
	}
	else
	{
		curPlaylist = playlists.begin()->second; 
	}
}

void App::logout()
{
	savePlaylists();
	accountManager.logout();
}

void App::registerAccount(const string& username, const string& password, bool VIP)
{
	accountManager.registerAccount(username, password, VIP);
	cout << "Registered account: " << username << (VIP ? " (VIP)" : "") << endl;
}

void App::loadPlaylists()
{
	string assetPath = accountManager.getAssetPath();
	ifstream file(assetPath);
	if (!file.is_open())
	{
		cerr << "Could not open playlists file: " << assetPath << endl;
		return;
	}
	// playlist format: name,song1,song2,...
	string line;
	while (getline(file, line))
	{
		istringstream iss(line);
		string name;
		getline(iss, name, ',');
		Playlist* playlist = new Playlist(name);
		string songTitle;
		while (getline(iss, songTitle, ','))
		{
			const Song* song = currentPlatform->getSong(songTitle);
			if (song)
			{
				playlist->addSong(song);
			}
			else
			{
				cout << "Song not found in platform: " << songTitle << endl;
			}
		}
		playlists[name] = playlist;
	}
	
}

void App::savePlaylists()
{
	if (accountManager.isLoggedIn())
	{
		string assetPath = accountManager.getAssetPath();
		ofstream file(assetPath);
		if (!file.is_open())
		{
			cerr << "Could not open playlists file for saving: " << assetPath << endl;
			return;
		}
		for (const auto& pair : playlists)
		{
			file << pair.first; // playlist name
			const Playlist* playlist = pair.second;
			for (const Song* song : playlist->songs)
			{
				file << "," << song->getTitle(); // song titles
			}
			file << "\n";
		}
		cout << "Playlists saved successfully." << endl;
	}
}

void App::showPlaylists() const
{
	if (playlists.empty())
	{
		cout << "No playlists available." << endl;
		return;
	}
	cout << "Available Playlists:" << endl;
	for (const auto& pair : playlists)
	{
		cout << "- " << pair.first << endl;
	}
}

void App::showAllSongs() const
{
	if (!currentPlatform)
	{
		cout << "No platform set. Please set a platform first." << endl;
		return;
	}
	
	cout << "Available Songs on " << currentPlatform->getName() << ": " << endl;
	currentPlatform->displayAllSongs();
}