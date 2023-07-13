// Section 20
// Challenge 4
// Identifying palindrome strings using a stack and queue
#include <cctype>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
#include <iomanip>

bool is_palindrome(const std::string& s)
{
    // You must implement this function.
    // Since we are learning the STL - use a stack and a queue to solve the problem.

    std::stack<char> phrase_stack;
    std::queue<char> phrase_queue;

    for(auto &ch : s){
        if(isalpha(ch)){
            phrase_stack.push(tolower(ch));
            phrase_queue.push(tolower(ch));
        }
    }

    while(phrase_queue.size() > 0){
        if (phrase_queue.front() != phrase_stack.top()){
            return false;
        }
        else{
            phrase_queue.pop();
            phrase_stack.pop();
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
        std::cout << std::setw(8) << std::left << is_palindrome(s);
        std::cout << " | ";
        std::cout << s << std::endl;
    }
    std::cout << std::endl;
    return 0;
}