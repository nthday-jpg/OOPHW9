#include "MusicPlatform.h"
#include "App.h"
#include "Playlist.h"
#include <iostream>

// Too many checks for null pointers, use observables or smart pointers in production code

int main()
{
	Platform spotify("musics/spotify.txt");
	spotify.addSong(new Song("Song1", "Artist1", "Lyrics1", Genre::Vietnamese, 2020));
	spotify.addSong(new Song("Song2", "Artist2", "Lyrics2", Genre::Western, 2021));
	spotify.addSong(new Song("Song3", "Artist3", "Lyrics3", Genre::KPop, 2022));
	spotify.addSong(new Song("Song4", "Artist4", "Lyrics4", Genre::Japanese, 2023));
	spotify.addSong(new Song("Song5", "Artist5", "Lyrics5", Genre::Chinese, 2024));
	spotify.addSong(new Song("Song6", "Artist6", "Lyrics6", Genre::Vietnamese, 2025));

	App app;
	app.setPlatform(&spotify);
	app.registerAccount("user1", "password1", true);
	app.login("user1", "password1");

	app.addPlaylist("My Playlist");
	app.addSongToPlaylist("My Playlist", "Song1");
	app.addSongToPlaylist("My Playlist", "Song2");
	app.playCurrentSong();
	app.playNextSong();

}