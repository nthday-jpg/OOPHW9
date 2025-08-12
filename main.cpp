#include "DungGiua.h"
#include "Song.h"
#include "MusicPlatform.h"
#include "App.h"

// Too many checks for null pointers, use observables or smart pointers in production code

int main()
{
	DungGiua dungGiua;
	dungGiua.registerPlatform("Spotify");
	App app;
	app.setPlatform(dungGiua.getPlatform("Spotify"));
	app.login("user1", "password1");
	app.addPlaylist("My Playlist");
	Platform* spotify = dungGiua.getPlatform("Spotify");
	
	app.addSongToPlaylist("My Playlist", "Song1");
	app.addSongToPlaylist("My Playlist", "Song2");
	app.playCurrentSong();
	app.playNextSong();

	app.logout();


}