#include <iostream>
#include <memory>
#include "Account.h"
#include "Checking_Account.h"
#include "Savings_Account.h"
#include "Trust_Account.h"
#include "Account_Util.h"

using namespace std;

void illegalbalancetext(std::string act_name){
    cerr << "Account \"" << act_name << "\" could not be created due to an illegal balance." << endl;
}

int main() {
    // test your code here

    // Test IllegalBalanceException
    {
        // Test Illegal Balance with checking account
        try{
            double balance {};
            cout << "Insert checking account starting balance: ";
            cin >> balance;

            Checking_Account checking {"Checking", balance};
            cout << "\nAccount checking successfully created" << endl;
            cout << checking << endl << endl;
        }
        catch (IllegalBalanceException){
            illegalbalancetext("checking");
        }

        // Test Illegal Balance with savings account

        try{
            double balance {};
            cout << "Insert savings account starting balance: ";
            cin >> balance;

            Savings_Account savings {"Savings", balance};
            cout << "\nAccount Savings successfully created" << endl;
            cout << savings << endl << endl;
        }
        catch (IllegalBalanceException){
            illegalbalancetext("Savings");
        }
    }

    std::cout << "Program completed successfully" << std::endl;
    return 0;
}

