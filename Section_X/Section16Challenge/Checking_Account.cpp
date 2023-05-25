#include "Checking_Account.h"

Checking_Account::Checking_Account(std::string name, double balance, double per_check_fee)
    : Account {name, balance}, per_check_fee{per_check_fee} {
}

bool Checking_Account::withdraw(double amount) {
    amount += per_check_fee;
    return Account::withdraw(amount);
}

bool Checking_Account::deposit(double amount){
    return Account::deposit(amount); //not sure if I can use a pure virtual function this way
}

void Checking_Account::print(std::ostream &os) const{
    os << "[Checking Account: " << name << ", Balance: $" << balance << ", Withdraw Fee: $" << per_check_fee << "]";
}

