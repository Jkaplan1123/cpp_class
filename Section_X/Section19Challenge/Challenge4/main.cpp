// Section 19
// Challenge 4
// Copy Romeo and Juliet with line numbers
#include <iostream>
#include <fstream>
#include <iomanip>


int main() {
    // std::string infile_name {"Section19Challenge/Challenge4/testfile.txt"};
    // std::string infile_name_debug {"testfile.txt"};

    std::string infile_name = "Section19Challenge/Challenge4/romeoandjuliet.txt";
    std::string infile_name_debug = "romeoandjuliet.txt";

    std::ifstream play;
    play.open(infile_name);

    if(!play){
        play.open(infile_name_debug);
        std::cout << "Program in debugging mode" << std::endl;
        if(!play){
            std::cerr << "Problem opening file" << std::endl;
            return 1;
        }
    }

    std::string outfile_name {"Section19Challenge/Challenge4/copyfile.txt"};
    std::string outfile_name_debug {"copyfile.txt"};
    std::ofstream play_copy;

    play_copy.open(outfile_name);

    if(!play_copy){
        play_copy.open(outfile_name_debug);
        if(!play_copy){
            std::cerr << "Problem creating output file" << std::endl;
            return 1;
        }
        std::cout << "Program in debugging mode" << std::endl;
    }

    std::string line {};
    int line_num {1};
    while (std::getline(play, line)){
        play_copy << std::setw(5) << std::right << line_num << " | ";
        play_copy << line << std::endl;
        line_num++;
    }
    
    play.close();
    play_copy.close();
    return 0;
}

