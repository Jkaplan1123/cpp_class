// Section 11
// Challenge 
/*
     Recall the challenge from Section 9 below.
    Your challenge for section 11 is to modularize your solution to the Section 9
    challenge by refactoring your solution so that it uses uses functions.
    
    You decide how to modularize the program.
    you can use my solution which is included in this file, or modularize your solution.
    
    Here are a few hints:
        - Create functions for each major function
        - Keep the functions small
        - Remember the Boss/Worker analogy
        - Keep the vector declaration in the main function and pass the vector object
          to any function that requires it

        DO NOT move the vector object outside main and make it a global variable.
    
        - You can start by defining a function that displays the menu
        - You can then define a function that reads the selection from the user and returns it in uppercase
        - Create functions for each menu option
        - Create functions that display the list of numbers, calculates the mean and so forth
        
    Take it one function at a time and take your time.
    If you get frustrated, take a break -- this isn't as easy as it looks the first time you do it!
    
    Finally,  don't forget to use function prototypes!
    
    Good luck -- I know you can do it!
*/
/*    
    This challenge is about using a collection (list) of integers and allowing the user
    to select options from a menu to perform operations on the list.
    
    Your program should display a menu options to the user as follows:
    
    P - Print numbers
    A - Add a number
    M - Display mean of the numbers
    S - Display the smallest number
    L - Display the largest number
    Q - Quit

    Enter your choice:
    
The program should only accept valid choices from the user, both upper and lowercase selections should be allowed.
If an illegal choice is made, you should display, "Unknown selection, please try again" and the menu options should be
displayed again.


If the user enters 'P' or 'p', you should display all of the elements (ints) in the list.
If the list is empty you should display "[] - the list is empty"
If the list is not empty then all the list element should be displayed inside square brackets separated by a space. 
For example, [ 1 2 3 4 5 ]
      
If the user enters 'A' or 'a' then you should prompt the user for an integer to add to the list 
which you will add to the list and then display it was added. For example, if the user enters 5
You should display, "5 added".
Duplicate list entries are OK

If the user enters 'M' or 'm'  you should calculate the mean or average of the elements in the list and display it.
If the list is empty you should display, "Unable to calculate the mean - no data"

If the user enters 'S' or 's' you should display the smallest element in the list.
For example, if the list contains [2 4 5 1],  you should display, "The smallest number is 1"
If the list is empty you should display, "Unable to determine the smallest number - list is empty"

If the user enters 'L' or 'l' you should display the largest element in the list
For example, if the list contains [2 4 5 1], you should display, "The largest number is 5"
If the list is empty you should display, "Unable to determine the largest number - list is empty"

If the user enters 'Q' or 'q' then you should display 'Goodbye" and the program should terminate.

Before you begin. Write out the steps you need to take and decide in what order they should be done.
Think about what loops you should use as well as what you will use for your selection logic.

This exercise can be challenging! It may likely take a few attempts before you complete it -- that's OK!

Finally, be sure to test your program as you go and at the end.

Hint: Use a vector!

Additional functionality if you wish to extend this program.

- search for a number in the list and if found display the number of times it occurs in the list
- clearing out the list (make it empty again) (Hint: the vector class has a .clear() method)
- don't allow duplicate entries
- come up with your own ideas!

Good luck!

*/
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

void display_menu();
char menu_select();
void print_list(const vector<int>& values);
void add_value(vector<int>& values);
void calculate_mean(const vector<int>& values);
void find_smallest_number(const vector <int> & values);
void find_largest_number(const vector <int> & values);


int main() {
    
    vector<int> values;
    char menu_selection {};


    do {

        // Get the user input from the menu
        menu_selection = menu_select();

        switch (menu_selection)
        {
        case 'P':
            cout << endl << "Print List Selected" << endl;

            print_list(values);

            
            break;
        
        case 'A':

            add_value(values);
            
            break;
        
        case 'M':
            cout << "Display mean" << endl;

            if (values.size() == 0){
                cout << "Unable to calculate the mean. No Data" << endl;
            }

            else {
                calculate_mean(values);
            }

            break;


        case 'S':
            cout << endl << "Display smallest" << endl;
            if (values.size() == 0){
                
                cout << "Unable to determine the smallest number - list is empty" << endl;
            }

            else{
                find_smallest_number(values);
            }
            break;

        case 'L':
            cout << endl << "Display largest" << endl;
            if (values.size() == 0){
                cout << "Unable to determine the largest number - list is empty" << endl;
            }

            else{
                find_largest_number(values);
            }

            break;


        case 'Q':
            cout << endl << "Goodbye" << endl;
            cout << endl;
            break;

        default:
            cout << "Unknown selection, please try again" << endl;
            cout << endl;
            break;
        }


        
    } while (!(menu_selection == 'Q'));

    return 0;
}

void display_menu(){

    cout << endl;
    cout << "Menu" << endl;
    cout << "--------" << endl;
    cout << "P - Print numbers" << endl;
    cout << "A - Add a number" << endl;
    cout << "M - Display mean of the numbers" << endl;
    cout << "S - Display the smallest number" << endl;
    cout << "L - Display the largest number" << endl;
    cout << "Q - Quit" << endl;

}

char menu_select(){
    display_menu();
    char menu_choice;

    cout << endl;
    cout << "Please select an option from the menu: ";
    cin >> menu_choice;
    

    return toupper(menu_choice);

}


void print_list(const vector<int>& values){
    if (values.size() == 0){
        
        cout << "[] - The list is empty" << endl;
    }

    else {
        cout << "[ ";
        for (auto entry : values){
            cout << entry << " ";
        }
        cout << "]" << endl;
    }
}

void add_value(vector<int>& values){
    
        int added_value {};
        cout << endl << "Please enter an integer to add to the end of the list: ";
        cin >> added_value;

        values.push_back(added_value);
        cout << added_value << " added to list";
    
}

void calculate_mean(const vector<int>& values){
    double running_total {0};

    for (auto value : values){
        running_total += value;
    }

    double mean_value = running_total / values.size();

    cout << "Mean value of elements in list: " << mean_value << endl;

}

void find_smallest_number(const vector <int> & values){
    int smallest_number {values[0]};

    for (auto value: values){
        if (smallest_number > value){
            smallest_number = value;
        }
    }

    cout << "The smallest number is: " << smallest_number << endl;
}

void find_largest_number(const vector <int> & values){
    int largest_number {values[0]};

    for (auto value: values){
        if (largest_number < value){
            largest_number = value;
        }
    }

    cout << "The largest number is: " << largest_number << endl;
}