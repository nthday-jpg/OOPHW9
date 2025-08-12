#include "DungGiua.h"
#include "Song.h"
#include "MusicPlatform.h"
#include "App.h"

// Too many checks for null pointers, use observables or smart pointers in production code
// Set platform before login
int main()
{
	DungGiua dungGiua;
	dungGiua.registerPlatform("Apple Music");
	App app;
	app.setPlatform(dungGiua.getPlatform("Spotify"));
	app.login("user1", "password1");
	Platform* spotify = dungGiua.getPlatform("Spotify");
	Platform* appleMusic = dungGiua.getPlatform("Apple Music");
	appleMusic->addExclusiveArtist("Artist5");
	Song* song7 = new Song("Song7", "Artist5", "Lyrics of Song5", Genre::Western, 2020);
	Song* song8 = new Song("Song8", "Artist5", "Lyrics of Song6", Genre::KPop, 2021);
	dungGiua.addSongToPlatform("Apple Music", song7);
	dungGiua.addSongToPlatform("Spotify", song8);
	app.addSongToPlaylist("My Playlist 2", "Song3");
	app.addSongToPlaylist("My Playlist 2", "Song4");
	app.playCurrentSong();
	app.setCurrentPlaylist("My Playlist 2");
	app.playNextSong();
	app.showTop5MostPlayedSongs();

	app.logout();


}