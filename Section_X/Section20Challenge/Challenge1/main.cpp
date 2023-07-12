// Section 20
// Challenge 1
// Identifying palindrome strings using a deque
#include <cctype>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

bool is_palindrome(const std::string& s)
{
    // You must implement this function.
    // Since we are learning the STL - use a deque to solve the problem.

    std::deque<char> phrase;

    for (auto &ch : s){
        if (isalpha(ch)){
            phrase.push_back(tolower(ch));
        }
    }

    // //Test to see if I created the deque correctly
    // std::cout << std::endl;
    // std::cout << "Input: " << s << std::endl;
    
    // std::cout << "Deque: ";
    // std::for_each(phrase.begin(), phrase.end(), [](char x) {std::cout << x;});
    // std::cout << std::endl;
    // std::cout << "----------------------------------" << std::endl;


    while (phrase.size() > 1){
        if (phrase.front() != phrase.back()){
            return false;
        }
        else{
            phrase.pop_back();
            phrase.pop_front();
        }
    }

    return true;
}

int main()
{
    std::vector<std::string> test_strings{ "a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
        "avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
        "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };
   
    std::cout << std::boolalpha;
    std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
    for(const auto& s : test_strings) {
        std::cout << std::setw(8) << std::left << is_palindrome(s) << " | " << s << std::endl;
        // is_palindrome(s);
    }
    std::cout << std::endl;
    return 0;
}