#include <iostream>
#include "Account_Util.h"

// Displays Account objects in a  vector of Account objects 
void display(const std::vector<Account> &accounts) {
    std::cout << "\n=== Accounts ==========================================" << std::endl;
    for (const auto &acc: accounts) 
        std::cout << acc << std::endl;
}

// Deposits supplied amount to each Account object in the vector
void deposit(std::vector<Account> &accounts, double amount) {
    std::cout << "\n=== Depositing to Accounts =================================" << std::endl;
    for (auto &acc:accounts)  {
        if (acc.deposit(amount)) 
            std::cout << "Deposited " << amount << " to " << acc << std::endl;
        else
            std::cout << "Failed Deposit of " << amount << " to " << acc << std::endl;
    }
}

// Withdraw amount from each Account object in the vector
void withdraw(std::vector<Account> &accounts, double amount) {
    std::cout << "\n=== Withdrawing from Accounts ==============================" <<std::endl;
    for (auto &acc:accounts)  {
        if (acc.withdraw(amount)) 
            std::cout << "Withdrew " << amount << " from " << acc << std::endl;
        else
            std::cout << "Failed Withdrawal of " << amount << " from " << acc << std::endl;
    } 
}


// Helper functions for Savings Account class

// Displays Savings Account objects in a  vector of Savings Account objects 
void display(const std::vector<Savings_Account> &accounts) {
    std::cout << "\n=== Savings Accounts ====================================" << std::endl;
    for (const auto &acc: accounts) 
        std::cout << acc << std::endl;
}

// Deposits supplied amount to each Savings Account object in the vector
void deposit(std::vector<Savings_Account> &accounts, double amount) {
    std::cout << "\n=== Depositing to Savings Accounts ==========================" << std::endl;
    for (auto &acc:accounts)  {
        if (acc.deposit(amount)) 
            std::cout << "Deposited " << amount << " to " << acc << std::endl;
        else
            std::cout << "Failed Deposit of " << amount << " to " << acc << std::endl;
    }
}

// Withdraw supplied amount from each Savings Account object in the vector
void withdraw(std::vector<Savings_Account> &accounts, double amount) {
    std::cout << "\n=== Withdrawing from Savings Accounts ======================" << std::endl;
    for (auto &acc:accounts)  {
        if (acc.withdraw(amount)) 
            std::cout << "Withdrew " << amount << " from " << acc << std::endl;
        else
            std::cout << "Failed Withdrawal of " << amount << " from " << acc << std::endl;
    } 
}


void display(const std::vector<Checking_Account> &accounts){
    std::cout << "\n=== Checking Accounts ====================================" << std::endl;
    for (const auto &acc: accounts){
        std::cout << acc << std::endl;
    }
}

// Deposit supplied amount to each Checking Account object in the vector
void deposit(std::vector<Checking_Account> &accounts, double amount){
    std::cout << "\n=== Depositing to Checking Accounts ======================" << std::endl;
    for (auto & acc: accounts){
        if (acc.deposit(amount)){
            std::cout << "Deposited " << amount << " from " << acc << std::endl;
            std::cout << "\t" << "New Balance: $" << acc.get_balance() << std::endl;
        }

        else{
            std::cout << "Failed deposit of " << amount << " from " << acc << std::endl;
        }
    }
}

// Withdraw supplied amount from each Checking Account object in the vector
void withdraw(std::vector<Checking_Account> &accounts, double amount){
    std::cout << "\n=== Withdrawing from Checking Accounts ======================" << std::endl;
    for (auto & acc: accounts){
        if (acc.withdraw(amount)){
            std::cout << "Withdrew " << amount << " from " << acc << std::endl;
            std::cout << "\t" << "Balance Remaining: $" << acc.get_balance() << std::endl;
        }

        else{
            std::cout << "Failed withdrawal of " << amount << " from " << acc << std::endl;
            std::cout << "\t" << "Balance: $" << acc.get_balance() << std::endl;
        }
    }
}


void display(const std::vector<Trust_Account> &accounts){
    std::cout << "\n=== Trust Accounts ====================================" << std::endl;
    for (const auto &acc: accounts){
        std::cout << acc << std::endl;
    }
}

// Deposit supplied amount to each Checking Account object in the vector
void deposit(std::vector<Trust_Account> &accounts, double amount){
    std::cout << "\n=== Depositing to Trust Accounts ======================" << std::endl;
    for (auto & acc: accounts){
        if (acc.deposit(amount)){
            std::cout << "Deposited " << amount << " from " << acc << std::endl;
            std::cout << "\t" << "New Balance: $" << acc.get_balance() << std::endl;
        }

        else{
            std::cout << "Failed deposit of " << amount << " from " << acc << std::endl;
        }
    }
}

// Withdraw supplied amount from each Trust Account object in the vector
void withdraw(std::vector<Trust_Account> &accounts, double amount){
    std::cout << "\n=== Withdrawing from Trust Accounts ======================" << std::endl;
    for (auto & acc: accounts){
        if (acc.withdraw(amount)){
            std::cout << "Withdrew " << amount << " from " << acc << std::endl;
            std::cout << "\t" << "Balance Remaining: $" << acc.get_balance() << std::endl;
            display_remaining_withdrawals(acc);
        }

        else{
            std::cout << "Failed withdrawal of " << amount << " from " << acc << std::endl;
            std::cout << "\t" << "Balance: $" << acc.get_balance() << std::endl;
            display_remaining_withdrawals(acc);
        }
    }
}

void display_remaining_withdrawals(Trust_Account &acc){
    std::cout << "\tThis account has ";
    if (acc.withdrawals_remaining() > 0){
        if (acc.withdrawals_remaining() == 1){
            std::cout << acc.withdrawals_remaining() << " additional withdrawal remaining this year" << std::endl;
        }

        else{
            std::cout << acc.withdrawals_remaining() << " additional withdrawals remaining this year" << std::endl;
        }
    }
    else{
        std::cout << "no further withdrawals this year." << std::endl;
    }
}