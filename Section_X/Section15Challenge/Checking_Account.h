#ifndef _CHECKING_ACCOUNT_H_
#define _CHECKING_ACCOUNT_H_
#include "Account.h"

// Checking Account is a type of Account
//   adds withdrawl fee
// Deposit - same as a regular account
// Withdraw:
//      Amount supplied to withdraw will be incremented by the withdrawal fee 
//      and then the updated amount will be withdrawn
//

class Checking_Account: public Account {
    friend std::ostream &operator<<(std::ostream &os, const Checking_Account &account);
private:
    static constexpr const char *def_name = "Unnamed Checking Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_withdraw_fee = 1.50;
protected:
    double withdraw_fee;
public:
    Checking_Account(std::string name = def_name, double balance = def_balance, double withdraw_fee = def_withdraw_fee);    
    bool withdraw(double amount);
    // Inherits the Account::deposit methods
};

#endif // _CHECKING_ACCOUNT_H_