// Section 16 
// Challenge 
#include <iostream>
#include <vector>
#include "Account.h"
#include "Savings_Account.h"
#include "Checking_Account.h"
#include "Trust_Account.h"
#include "Account_Util.h"

using namespace std; 


void reference_display (Account const &account){
    cout << account << endl;
}

int main() {
    cout.precision(2);
    cout << fixed;
   
    // Savings 

    Savings_Account superman {"Superman"};
    Savings_Account batman {"Batman", 2000};
    Savings_Account wonderwoman {"Wonderwoman", 5000, 5.0};

    vector<Account *> sav_accounts;
    sav_accounts.push_back(&superman);
    sav_accounts.push_back(&batman);
    sav_accounts.push_back(&wonderwoman);

    display(sav_accounts);
    deposit(sav_accounts, 1000);
    withdraw(sav_accounts,2000);
   
   // Checking
    Checking_Account kirk {"Kirk"} ;
    Checking_Account spock {"Spock", 2000} ;
    Checking_Account scotty {"Scotty", 5000} ;

    vector<Account *> check_accounts;
    check_accounts.push_back(&kirk);
    check_accounts.push_back(&spock);
    check_accounts.push_back(&scotty);

    display(check_accounts);
    deposit(check_accounts, 1000);
    withdraw(check_accounts, 2000);

    // Trust - using pointers
    Account *jack = new Trust_Account ("Jack", 10000, 5.0);
    Account *layne = new Trust_Account("Layne", 20000, 4.0);
    Account *glynn = new Trust_Account("Glynn", 30000);

    vector<Account *> trust_accounts;
    trust_accounts.push_back(jack);
    trust_accounts.push_back(layne);
    trust_accounts.push_back(glynn);

    display(trust_accounts);
    deposit(trust_accounts, 1000);
    withdraw(trust_accounts, 3000);
    
    // Withdraw 5 times from each trust account
    // All withdrawals should fail if there are too many withdrawals or if the withdrawl is > 20% of the balance
    for (int i=1; i<=5; i++){
        withdraw(trust_accounts, 1000);
    }

    delete jack;
    delete layne;
    delete glynn;
    
    Account *p1 = new Checking_Account("Larry", 10000);
    Account *p2 = new Savings_Account("Moe", 1000);
    Account *p3 = new Trust_Account("Curly"); 
    
    vector<Account *> accounts {p1,p2,p3};
    
    display(accounts);
    deposit(accounts, 1000);
    withdraw(accounts, 2000);
    
    display(accounts);
    
    delete p1;
    delete p2;
    delete p3;

    // Try out passing in regular objects (not pointers) to a function using
    // base class references
    cout << "\nTry using Base Class Reference:" << endl;
    reference_display(wonderwoman);
    reference_display(kirk);
    reference_display(Trust_Account {"Jack"});
    
    return 0;
}

