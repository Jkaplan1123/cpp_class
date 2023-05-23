#include "Trust_Account.h"

// Constructor
Trust_Account::Trust_Account(std::string name, double balance, double int_rate, double max_withdraw_percentage,
    int max_annual_withdrawals, double deposit_bonus_threshold, double deposit_bonus_amount, int current_withdrawals) 
    : Savings_Account {name, balance, int_rate}, max_withdraw_percentage{max_withdraw_percentage},
    max_annual_withdrawals{max_annual_withdrawals}, deposit_bonus_threshold{deposit_bonus_threshold},
    deposit_bonus_amount{deposit_bonus_amount}, current_withdrawals{current_withdrawals} {
}

// Try to withdraw the selected amount given the constraints on withdrawal amounts and 
// the number of annual withdrawals 
bool Trust_Account::withdraw(double amount){

    double desired_withdraw_percent = amount/balance;

    // Check to see (1) if the account has exceeded its maximum number of withdrawls for the year and 
    // (2) if the withdrawl amount is below the maximum withdrawl percentage

    if ((current_withdrawals < max_annual_withdrawals) && (desired_withdraw_percent < (max_withdraw_percentage/100))){
        if(Account::withdraw(amount)){
            current_withdrawals++;
            return true;
        }
        else{
            return false;
        }
    }

    else{
        return false;
    }
}

// Adds a bonus amount to the deposit if the deposit exceeds a certain threshold
bool Trust_Account::deposit(double amount){
    if (amount >= deposit_bonus_threshold){
        amount += deposit_bonus_amount;
    }

    return Savings_Account::deposit(amount);
}

// returns the number of withdrawls used this year
int Trust_Account::withdrawals_used() const{
    return current_withdrawals;
} 

// returns the number of withdrawls reamining this year
int Trust_Account::withdrawals_remaining() const{
    return (max_annual_withdrawals - current_withdrawals);
} 

std::ostream &operator<<(std::ostream &os, const Trust_Account &account) {
    os << "[Trust Account: " << account.name << ", Balance: $ " << account.balance << ", Max Withdrawal Percentage: " << account.max_withdraw_percentage << "%]";
    return os;
}