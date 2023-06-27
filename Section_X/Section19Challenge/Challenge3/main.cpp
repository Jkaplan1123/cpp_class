// Section 19
// Challenge 3
// Word counter
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

// using namespace std;

int main() {

    // std::string file_name {"Section19Challenge/Challenge3/testfile.txt"};
    // std::string debug_file_name {"testfile.txt"};

    std::string file_name = "Section19Challenge/Challenge3/romeoandjuliet.txt";
    std::string debug_file_name = "romeoandjuliet.txt";

    std::ifstream play;
    play.open(file_name);

    if(!play){
        play.open(debug_file_name);
        std::cout << "Program in debugging mode" << std::endl;
        if(!play){
            std::cerr << "Problem opening file" << std::endl;
            return 1;
        }
    }

    std::string search_word {};
    std::cout << "\nPlease enter the substring to search for: ";
    std::cin >> search_word;

    int substring_tracker {0};
    int word_count {0};
    std::string current_word {};
    while(!play.eof()){
        play >> current_word;
        word_count++;
        int found = current_word.find(search_word);
        if(found != std::string::npos){
            substring_tracker++;
        }
    }
    play.close();

    std::cout << "Found the substring \"" << search_word << "\" " << substring_tracker;
    if (substring_tracker == 1){
        std::cout << " time." << std::endl;
    }
    else{
        std::cout << " times." << std::endl;
    }

    std::cout << word_count << " words searched" << std::endl;

    std::cout << std::endl;
    return 0;
}

