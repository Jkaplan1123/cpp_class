#include "Checking_Account.h"

// Constructor
Checking_Account::Checking_Account(std::string name, double balance, double withdraw_fee) 
    : Account {name, balance}, withdraw_fee{withdraw_fee}{
}

// Try to withdraw the selected amount + the withdrawl fee charge
bool Checking_Account::withdraw(double amount){
    return Account::withdraw((amount + withdraw_fee));
}

std::ostream &operator<<(std::ostream &os, const Checking_Account &account) {
    os << "[Checking Account: " << account.name << ", Balance: $" << account.balance << ", Withdraw Fee: $" << account.withdraw_fee << "]";
    return os;
}


// class Checking_Account: public Account {
//     friend std::ostream &operator<<(std::ostream &os, const Checking_Account &account);
// private:
//     static constexpr const char *def_name = "Unnamed Checking Account";
//     static constexpr double def_balance = 0.0;
//     static constexpr double def_withdraw_fee = 1.0;
// protected:
//     double int_rate;
// public:
//     // Checking_Account(std::string name = def_name, double balance = def_balance, double withdraw_fee = def_withdraw_fee);    
//     bool withdraw(double amount);
//     // Inherits the Account::deposit methods
// };