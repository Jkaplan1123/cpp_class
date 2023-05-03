/*
Jack Kaplan
2 May 2023
Assignment 1 - Letter Pyramid
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    
    string input_str {};

    // string test_str {"abcdefghij"};
    // input_str = test_str;

    cout << "Please input values to convert into a letter pyramid: ";
    getline(cin, input_str);
    cout << "Input: " << input_str << endl;
    cout << "---------------------------" << endl;
    cout << endl;

    // Note: n_i refers to the ith character in the input string
    for (int i = 0; i < input_str.length(); i++){
        string row_output {};

        // number of leading and trailing spaces required for pyramid shape
        int num_spaces_required = input_str.length()-i;

        // Leading Spaces
        for (int k = 0; k < num_spaces_required; k++){
            row_output += " ";
        }

        // n_0 to n_(i-1) inclusive
        for (int j = 0; j < i; j++){
            row_output += input_str.at(j);
        }

        // n_i
        row_output += input_str.at(i);

        // n_(i-1) to n_0 inclusive
        for (int j = i-1; j >= 0; j--){
            row_output += input_str.at(j);
        }

        // Trailing Spaces
        for (int k = num_spaces_required; k >= 0; k--){
            row_output += " ";
        }

        cout << row_output << endl;
    }


    return 0;
}