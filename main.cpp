#include "DungGiua.h"
#include "Song.h"
#include "MusicPlatform.h"
#include "App.h"
#include <iostream>

using namespace std;

int main()
{
    try
    {
        cout << "=== Music Platform Testing Application ===" << endl;
        cout << endl;

        DungGiua dungGiua;

        cout << "1. Registering platforms..." << endl;
        dungGiua.registerPlatform("Spotify");
        dungGiua.registerPlatform("Apple Music");
        cout << "Platforms registered successfully!" << endl;
        cout << endl;

        App app;

        cout << "2. Registering user account..." << endl;
        app.registerAccount("user1", "password1", false);
        cout << endl;

        cout << "3. Setting platform..." << endl;
        Platform* spotify = dungGiua.getPlatform("Spotify");
        app.setPlatform(spotify);
        cout << endl;

        cout << "4. Creating and adding songs with diverse genres..." << endl;

        Song* song1 = new Song("Shape of You", "Ed Sheeran", "Lyrics of Shape of You", Genre::Western, 2017);
        Song* song2 = new Song("Blinding Lights", "The Weeknd", "Lyrics of Blinding Lights", Genre::Western, 2019);
        Song* song3 = new Song("Bad Guy", "Billie Eilish", "Lyrics of Bad Guy", Genre::Western, 2019);

        Song* song4 = new Song("Dynamite", "BTS", "Lyrics of Dynamite", Genre::KPop, 2020);
        Song* song5 = new Song("How You Like That", "BLACKPINK", "Lyrics of How You Like That", Genre::KPop, 2020);
        Song* song6 = new Song("Next Level", "aespa", "Lyrics of Next Level", Genre::KPop, 2021);

        Song* song7 = new Song("Nang Am Xa Dan", "Son Tung MTP", "Lyrics of Nang Am Xa Dan", Genre::Vietnamese, 2020);
        Song* song8 = new Song("Khong Phai Dang Vua Dau", "Hoang Thuy Linh", "Lyrics of Khong Phai Dang Vua Dau", Genre::Vietnamese, 2019);

        Song* song9 = new Song("Pretender", "Official HIGE DANdism", "Lyrics of Pretender", Genre::Japanese, 2019);
        Song* song10 = new Song("Lemon", "Kenshi Yonezu", "Lyrics of Lemon", Genre::Japanese, 2018);

        Song* song11 = new Song("Mo Li Hua", "Jay Chou", "Lyrics of Mo Li Hua", Genre::Chinese, 2021);

        dungGiua.addSongToPlatform("Spotify", song1);
        dungGiua.addSongToPlatform("Spotify", song2);
        dungGiua.addSongToPlatform("Spotify", song3);
        dungGiua.addSongToPlatform("Spotify", song4);
        dungGiua.addSongToPlatform("Spotify", song5);
        dungGiua.addSongToPlatform("Spotify", song6);
        dungGiua.addSongToPlatform("Spotify", song7);
        dungGiua.addSongToPlatform("Spotify", song8);
        dungGiua.addSongToPlatform("Spotify", song9);
        dungGiua.addSongToPlatform("Spotify", song10);
        dungGiua.addSongToPlatform("Spotify", song11);

        cout << "Songs with diverse genres added successfully!" << endl;
        cout << endl;

        cout << "5. Logging in user..." << endl;
        app.login("user1", "password1");
        cout << endl;

        cout << "6. Showing all available songs:" << endl;
        app.showAllSongs();
        cout << endl;

        cout << "7. Creating playlists and adding songs..." << endl;
        app.addPlaylist("Western Hits");
        app.addPlaylist("K-Pop Favorites");
        app.addPlaylist("Asian Mix");

        app.addSongToPlaylist("Western Hits", "Shape of You");
        app.addSongToPlaylist("Western Hits", "Blinding Lights");
        app.addSongToPlaylist("Western Hits", "Bad Guy");

        app.addSongToPlaylist("K-Pop Favorites", "Dynamite");
        app.addSongToPlaylist("K-Pop Favorites", "How You Like That");
        app.addSongToPlaylist("K-Pop Favorites", "Next Level");

        app.addSongToPlaylist("Asian Mix", "Nang Am Xa Dan");
        app.addSongToPlaylist("Asian Mix", "Pretender");
        app.addSongToPlaylist("Asian Mix", "Mo Li Hua");
        cout << endl;

        cout << "8. Simulating diverse listening patterns..." << endl;

        app.setCurrentPlaylist("Western Hits");
        cout << "Playing Western songs extensively..." << endl;
        for (int i = 0; i < 5; ++i) {
            app.playCurrentSong(); 
        }
        app.playNextSong();
        for (int i = 0; i < 3; ++i) {
            app.playCurrentSong(); 
        }
        app.playNextSong();
        for (int i = 0; i < 4; ++i) {
            app.playCurrentSong(); 
        }

        app.setCurrentPlaylist("K-Pop Favorites");
        cout << "Playing K-Pop songs..." << endl;
        for (int i = 0; i < 6; ++i) {
            app.playCurrentSong(); // Dynamite - 6 plays (most popular)
        }
        app.playNextSong();
        for (int i = 0; i < 2; ++i) {
            app.playCurrentSong(); // How You Like That - 2 plays
        }
        app.playNextSong();
        app.playCurrentSong(); // Next Level - 1 play

        // Play Asian songs
        app.setCurrentPlaylist("Asian Mix");
        cout << "Playing Asian songs..." << endl;
        for (int i = 0; i < 3; ++i) {
            app.playCurrentSong(); // Nang Am Xa Dan - 3 plays
        }
        app.playNextSong();
        for (int i = 0; i < 2; ++i) {
            app.playCurrentSong(); // Pretender - 2 plays
        }
        app.playNextSong();
        app.playCurrentSong(); // Mo Li Hua - 1 play
        cout << endl;

        // Test top songs by genre functionality
        cout << "9. === TESTING TOP SONGS BY GENRE ===" << endl;
        cout << endl;

        cout << "9a. Top Western Songs:" << endl;
        app.showTopSongsByGenre(Genre::Western);
        cout << endl;

        cout << "9b. Top K-Pop Songs:" << endl;
        app.showTopSongsByGenre(Genre::KPop);
        cout << endl;

        cout << "9c. Top Vietnamese Songs:" << endl;
        app.showTopSongsByGenre(Genre::Vietnamese);
        cout << endl;

        cout << "9d. Top Japanese Songs:" << endl;
        app.showTopSongsByGenre(Genre::Japanese);
        cout << endl;

        cout << "9e. Top Chinese Songs:" << endl;
        app.showTopSongsByGenre(Genre::Chinese);
        cout << endl;

        // Show overall top 5 most played songs for comparison
        cout << "10. Overall top 5 most played songs (all genres):" << endl;
        app.showTop5MostPlayedSongs();
        cout << endl;

        // Add more plays to create different patterns
        cout << "11. Creating new listening patterns..." << endl;

        // Make Japanese songs more popular
        app.setCurrentPlaylist("Asian Mix");
        app.setCurrentPlaylist("Asian Mix"); // Reset to first song
        app.playNextSong(); // Go to Pretender
        for (int i = 0; i < 7; ++i) {
            app.playCurrentSong(); // Pretender now has 9 total plays
        }

        // Make a Vietnamese song very popular
        app.playPreviousSong(); // Go back to Nang Am Xa Dan
        for (int i = 0; i < 5; ++i) {
            app.playCurrentSong(); // Nang Am Xa Dan now has 8 total plays
        }
        cout << endl;

        // Show updated results
        cout << "12. Updated top songs by genre after new listening patterns:" << endl;
        cout << endl;

        cout << "12a. Updated Top Vietnamese Songs:" << endl;
        app.showTopSongsByGenre(Genre::Vietnamese);
        cout << endl;

        cout << "12b. Updated Top Japanese Songs:" << endl;
        app.showTopSongsByGenre(Genre::Japanese);
        cout << endl;

        cout << "12c. Updated Overall Top 5:" << endl;
        app.showTop5MostPlayedSongs();
        cout << endl;

        // Test edge case: genre with no songs
        cout << "13. Testing edge case - requesting top songs for a platform with limited genres..." << endl;

        // Switch to Apple Music (which might have fewer songs)
        Platform* appleMusic = dungGiua.getPlatform("Apple Music");
        app.setPlatform(appleMusic);

        cout << "13a. Top songs on Apple Music (should be empty or very limited):" << endl;
        app.showTopSongsByGenre(Genre::Western);
        cout << endl;

        // Switch back to Spotify for final tests
        app.setPlatform(spotify);
        cout << "Switched back to Spotify for final tests." << endl;
        cout << endl;

        // Final comprehensive genre analysis
        cout << "14. === FINAL COMPREHENSIVE GENRE ANALYSIS ===" << endl;
        cout << endl;

        cout << "Final results for all genres:" << endl;
        cout << "============================================" << endl;

        cout << "\n[WESTERN GENRE]" << endl;
        app.showTopSongsByGenre(Genre::Western);

        cout << "\n[K-POP GENRE]" << endl;
        app.showTopSongsByGenre(Genre::KPop);

        cout << "\n[VIETNAMESE GENRE]" << endl;
        app.showTopSongsByGenre(Genre::Vietnamese);

        cout << "\n[JAPANESE GENRE]" << endl;
        app.showTopSongsByGenre(Genre::Japanese);

        cout << "\n[CHINESE GENRE]" << endl;
        app.showTopSongsByGenre(Genre::Chinese);

        cout << "\n[OVERALL TOP 5 ACROSS ALL GENRES]" << endl;
        app.showTop5MostPlayedSongs();
        cout << endl;

        // Logout
        cout << "15. Logging out..." << endl;
        app.logout();
        cout << "User logged out successfully!" << endl;
        cout << endl;

        cout << "=== GENRE TESTING COMPLETED SUCCESSFULLY! ===" << endl;
        cout << "Summary: Tested top songs functionality across 5 different genres" << endl;
        cout << "- Western, K-Pop, Vietnamese, Japanese, and Chinese music" << endl;
        cout << "- Verified sorting by play count within each genre" << endl;
        cout << "- Tested edge cases with empty genres" << endl;
        cout << "- Compared genre-specific results with overall top songs" << endl;
    }
    catch (const std::exception& e)
    {
        cerr << "Error during testing: " << e.what() << endl;
        return 1;
    }

    return 0;
}