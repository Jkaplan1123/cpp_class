// Section 15
// Challenge 
#include <iostream>
#include <vector>
#include "Savings_Account.h"
#include "Account_Util.h"

using namespace std;

int main() {
    cout.precision(2);
    cout << fixed;
   
    // Accounts
    vector<Account> accounts;
    accounts.push_back(Account {});
    accounts.push_back(Account {"Larry"});
    accounts.push_back(Account {"Moe", 2000} );
    accounts.push_back(Account {"Curly", 5000} );
    
    display(accounts);
    deposit(accounts, 1000);
    withdraw(accounts,2000);
    
    // Savings 

    vector<Savings_Account> sav_accounts;
    sav_accounts.push_back(Savings_Account {} );
    sav_accounts.push_back(Savings_Account {"Superman"} );
    sav_accounts.push_back(Savings_Account {"Batman", 2000} );
    sav_accounts.push_back(Savings_Account {"Wonderwoman", 5000, 5.0} );

    display(sav_accounts);
    deposit(sav_accounts, 1000);
    withdraw(sav_accounts, 2000);
    

    vector<Checking_Account> chk_accounts;
    chk_accounts.push_back(Checking_Account {} );
    chk_accounts.push_back(Checking_Account {"Alpha"} );
    chk_accounts.push_back(Checking_Account {"Bravo", 1000} );
    chk_accounts.push_back(Checking_Account {"Charlie", 1000, 0});
    chk_accounts.push_back(Checking_Account {"Delta", 5000, 2.5} );

    display(chk_accounts);
    deposit(chk_accounts, 1000);
    withdraw(chk_accounts, 2000);


    // Trust_Account(std::string name = def_name, double balance = def_balance, double int_rate = def_int_rate,
    //     double max_withdraw_percentage = def_max_withdrawl_percentage, int max_annual_withdrawals = def_maximum_annual_withdrawals,
    //     double deposit_bonus_threshold = def_deposit_bonus_threshold, double deposit_bonus_amount = def_deposit_bonus_amount,
    //     int current_withdrawals = 0);
    
    vector<Trust_Account> trst_accts;
    // trst_accts.push_back(Trust_Account {});
    trst_accts.push_back(Trust_Account {"Glynn", 0.0, 0.0, 20, 1});
    trst_accts.push_back(Trust_Account {"Layne", 10000.0, 0.0, 10, 2});
    trst_accts.push_back(Trust_Account {"Jack", 10000});

    display(trst_accts);
    withdraw(trst_accts, 1200);
    deposit(trst_accts, 5000);
    withdraw(trst_accts, 1000);
    withdraw(trst_accts, 800);
    withdraw(trst_accts, 1);


    return 0;
}

