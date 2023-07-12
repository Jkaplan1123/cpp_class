// Section 20
// Challenge 2
//  Lists

#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

class Song {
    friend std::ostream &operator<<(std::ostream &os, const Song &s);
    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    Song(std::string name, std::string artist, int rating)
            : name{name}, artist{artist}, rating{rating} {}
    std::string get_name() const {
        return name;
    }
    std::string get_artist() const {
        return artist;
    }
    int get_rating() const {
        return rating;
    }
    
    bool operator<(const Song &rhs) const  {
        return this->name < rhs.name;
    }
    
    bool operator==(const Song &rhs) const  {
        return this->name == rhs.name;
    }
};

std::ostream &operator<<(std::ostream &os, const Song &s) {
    os << std::setw(20) << std::left << s.name
       << std::setw(30) << std::left << s.artist
       << std::setw(2) << std::left << s.rating;
       return os;
}

void display_menu() {
    std::cout << "\nF - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "L - List the current playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song &song) {
    // This function should display 
    // Playing: followed by the song that is playing
   
    std::cout << "Playing: " << song.get_name() << " by " << song.get_artist() << ". Your Rating: " << song.get_rating() << "/5 stars" << std::endl;
}

void generate_header(const int song_width, const int artist_width, const int rating_width, const int total_width){
    

    // Header
    std::cout << std::endl;
    std::cout << std::setw(song_width) << std::left << "Song Name";
    std::cout << std::setw(artist_width) << std::left << "Artist Name";
    std::cout << std::setw(rating_width) << std::right << "Rating";
    std::cout << std::endl;

    std::cout << std::setw(total_width) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ');

}

void display_playlist(const std::list<Song> &playlist, const Song &current_song) {
    // This function should display the current playlist 
    // and then the current song playing.
    
    const int song_width = 20;
    const int artist_width = 35;
    const int rating_width = 8;
    const int total_width = song_width + artist_width + rating_width;

    generate_header(song_width, artist_width, rating_width, total_width);

    for (auto song : playlist){
        std::cout << std::setw(song_width) << std::left << song.get_name();
        std::cout << std::setw(artist_width) << std::left << song.get_artist();
        std::cout << std::setw(rating_width) << std::right << song.get_rating();
        std::cout << std::endl;
    }

    std::cout << std::endl;

    play_current_song(current_song);
}

std::list<Song>::iterator goto_next_song( std::list<Song> &playlist, const std::list<Song>::iterator &current_song){

    std::list<Song>::iterator next_song {std::next(current_song, 1)};
    // wrap back to first song if at the end of the playlist
    if (next_song == playlist.end()){
        return playlist.begin();
    }
    else{
        return next_song;
    }
}

std::list<Song>::iterator previous_song(std::list<Song> &playlist, const std::list<Song>::iterator &current_song){

    // wrap to last song if at the beginning of the playlist
    if (current_song == playlist.begin()){
        return (prev(playlist.end(), 1));
    }
    else{
        return std::prev(current_song, 1);
    }
}

int main() {

    std::list<Song> playlist{
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weekend and K. Lamar",  4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroone 5",                 4},
            {"Whatever It Takes", "Imagine Dragons",           3}          
    };
    
    std::list<Song>::iterator current_song = playlist.begin();
    
    // std::cout << "To be implemented" << std::endl;
    // Your program logic goes here

    char menu_selection;
   do {
        display_menu();
        // std::cout << std::endl << "Please make a selection: ";
        std::cin >> menu_selection;
        menu_selection = toupper(menu_selection);
        std::cout << std::endl;

        switch(menu_selection){
            case 'F':
                current_song = playlist.begin();
                play_current_song(*current_song);
                break;
            
            case 'N':
                //TODO: play next song - make sure that playlist wraps
                current_song = goto_next_song(playlist, current_song); // go to next song
                play_current_song(*current_song); // play the song
                break;
            
            case 'P':
                //TODO: play previous song - make sure that playlist wraps
                current_song = previous_song(playlist, current_song); // go to previous song
                play_current_song(*current_song); // play the song
                break;
            
            case 'A':
            {
                //TODO: Add new song before current song in playlist

                // Create new song
                std::string song_name;
                std::string artist_name;
                int song_rating;

                std::cout << "Enter Song Name: ";
                std::getline(std::cin >> std::ws, song_name);

                std::cout << "Enter Artist Name: ";
                std::getline(std::cin >> std::ws, artist_name);

                std::cout << "Enter Rating out of 5: ";
                std::cin >> song_rating;

                Song new_song {song_name, artist_name, song_rating};

                // Add new song to playlist before current song
                current_song = playlist.insert(current_song, new_song);
                
                // Play the newly inseted song
                play_current_song(*current_song);

                //TODO: play newly added song
                break;
            }
                
            
            case 'L':
                display_playlist(playlist, *current_song);
                break;

            case 'Q':
                break;
            
            default:
                std::cout << "Unknown selection, please try again" << std::endl;
                std::cout << std::endl;
                break;
        }
    
    std::cout << std::endl;
        
    }while (menu_selection != 'Q');


    std::cout << "Thanks for listening!" << std::endl;
    return 0;
}