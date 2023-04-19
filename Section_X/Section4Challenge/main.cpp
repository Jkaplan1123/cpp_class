#include <iostream>

using namespace std;

int main(){
    int favorite_number;
    cout << "Enter your favorite number between 1 and 100: ";
    cin >> favorite_number; //Read user input from console and store as favorite_number
    
    // Just for fun, makes sure they really inputting a number between 1 and 100
    int iter = 1;
    while (favorite_number < 1 or favorite_number > 100){
        
        if (iter > 4){
            cout << "You're hopeless. Please follow instructions next time." << endl;
            return 0;
        }
        
        cout << "Please try again. Enter your favorite number between 1 and 100: \n";
        cin >> favorite_number;
        
        iter++;

    }
    
    cout << "Me too!" << endl;
    cout << favorite_number << " really is my favorite number" << endl;
//    cout << "Test" << std::endl;
    return 0;
}