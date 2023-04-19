#include <iostream>

int main(){
    int favorite_number;
    std::cout << "Enter your favorite number between 1 and 100: ";
    std::cin >> favorite_number; //Read user input from console and store as favorite_number
    std::cout << "Me too!" << std::endl;
    return 0;
}