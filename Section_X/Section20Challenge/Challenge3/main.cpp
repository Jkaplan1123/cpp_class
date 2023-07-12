// Section 20
// Challenge 3  
// Maps and Sets

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <iomanip>
#include <cstring>

// Used for Part1
// Display the word and count from the 
// std::map<std::string, int>

void display_words(const std::map<std::string, int> &words) {
    std::cout << std::setw(12) << std::left << "\nWord"
                << std::setw(7) << std::right << "Count"<< std::endl;
    std::cout << "===================" << std::endl;
    for (auto pair: words)
        std::cout << std::setw(12) << std::left << pair.first 
                       << std::setw(7) << std::right << pair.second << std::endl;
}

// Used for Part2
// Display the word and occurences from the 
// std::map<std::string, std::set<int>>

void display_words(const std::map<std::string, std::set<int>> &words)
{
     std::cout << std::setw(12) << std::left << "\nWord"
                << "Occurrences"<< std::endl;
    std::cout << "=====================================================================" << std::endl;
    for (auto pair: words) {
        std::cout << std::setw(12) << std::left << pair.first 
                       << std::left << "[ ";
        for (auto i: pair.second) 
            std::cout << i << " ";
        std::cout << "]" << std::endl;
    }
}

// This function removes periods, commas, semicolons and colon in 
// a string and returns the clean version
std::string clean_string(const std::string &s) {
    std::string result;
    for (char c: s) {
        if (c == '.' || c == ',' || c == ';' || c == ':')
            continue;
        else
            result += c;
            // result += std::tolower(c);
    }
    return result;
}

// Part1 process the file and builds a map of words and the 
// number of times they occur in the file

void part1(std::string infile_name) {
    std::map<std::string, int> words;
    std::string line;       
    std::string word;   
   



    std::ifstream in_file {infile_name};

    if (in_file) {
        
        // You implement this code

        while(std::getline(in_file, line)){
            

            line = clean_string(line);
            std::stringstream ss_line {line};
            while (ss_line >> word){
                auto key_search = words.find(word);
                if (key_search == words.end()){
                    words.insert(std::make_pair(word, 1));
                }
                else{
                    words.at(word) += 1;
                }
            }
        }

        in_file.close();
        display_words(words);
    } else {
        std::cerr << "Error opening input file" << std::endl;
    }
}
    
// Part2 process the file and builds a map of words and a 
// set of line numbers in which the word appears
void part2(std::string infile_name) {
    std::map<std::string, std::set<int>> words;
    std::string line;
    std::string word;
    std::ifstream in_file {infile_name};
    if (in_file) {
     
        // You implement this code
        
        int line_num {1};

        while(std::getline(in_file, line)){
            line = clean_string(line);
            std::stringstream ss_line {line};
            while (ss_line >> word){
                auto key_search = words.find(word);
                if (key_search == words.end()){
                    words.insert(std::make_pair(word, std::set<int>{line_num}));
                }
                else{
                    (words.at(word)).insert(line_num);
                }

            line_num++;
            }
        }

        
        in_file.close();
        display_words(words);
    } else {
        std::cerr << "Error opening input file" << std::endl;
    }
}

int main() {

    // std::string infile_name{"testfile.txt"};
    // std::string infile_name {"Section20Challenge/Challenge3/testfile.txt"};

    std::string infile_name {"Section20Challenge/Challenge3/words.txt"};

    part1(infile_name);
    part2(infile_name);
    return 0;
}

