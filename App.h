#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Playlist.h"
#include "MusicPlatform.h"
#include "AccountManager.h"

class App
{
	std::string accountPath; 

	std::unordered_map<std::string, Playlist*> playlists; 
	Playlist* curPlaylist; 
	Platform* currentPlatform;
	AccountManager accountManager; 

public:

	App();
	~App();

	void login(const std::string& username, const std::string& password);
	void logout();
	void registerAccount(const std::string& username, const std::string& password, bool VIP = false);

	void setPlatform(Platform* platform);
	void addPlaylist(const std::string& name);
	void removePlaylist(const std::string& name);
	void setCurrentPlaylist(const std::string& name);

	void loadPlaylists();
	void savePlaylists();
	void addSongToPlaylist(const std::string& playlist, const std::string& title);
	void playNextSong();
	void playPreviousSong();
	void removeCurrentSong();
	void playCurrentSong();
	void stopCurrentSong();

	void showPlaylists() const;
	void showAllSongs() const;

	void showCurrentPlaylist() const;
	void showTop5MostPlayedSongs() const;
	void showTopSongsByGenre(Genre genre) const;

private:
	Playlist* getPlaylistByName(const std::string& name);
};