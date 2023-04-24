#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    int value_owed {0};
    cout << "Input change due in cents: ";
    cin >> value_owed;
    
    cout << "You are due " << value_owed << " cents." << endl;
    
    // Initialize change counter
    const int dollar_value {100};
    const int quarter_value {25};
    const int dime_value {10};
    const int nickle_value {5};
    const int penny_value {1};
    
    vector<string> coin_names {"dollars", "quarters", "dimes", "nickles", "pennies"};
    vector<int> coin_values {dollar_value, quarter_value, dime_value, nickle_value, penny_value};
    vector<int> coin_number (coin_values.size(), 0);

    int remaining_change {value_owed};

    for (unsigned int idx = 0; idx < coin_names.size(); idx++){

        if (remaining_change >= coin_values[idx]){

            // Get the number of the current coin that need to be dispensed. Not as neat as possible but I was cautious of taking advantage of the properties of integer division
            coin_number[idx] = (remaining_change - (remaining_change % coin_values[idx])) / coin_values[idx];

            // Use modular division to determine how much change is left to be dispensed
            remaining_change = remaining_change % coin_values[idx];
        }
    
        cout << "Number of " << coin_names[idx] << " to be dispensed: " << coin_number[idx] << endl;
    }

    cout << "Thank You" << endl;



    return 0;
}