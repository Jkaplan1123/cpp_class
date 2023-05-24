#ifndef _CHECKING_ACCOUNT_H_
#define _CHECKING_ACCOUNT_H_
#include <iostream>
#include <string>
#include "Account.h"

class Checking_Account: public Account {
    friend std::ostream &operator<<(std::ostream &os, const Checking_Account &account);
private:
    static constexpr const char *def_name = "Unnamed Checking Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_per_check_fee = 1.5;
protected:
    double per_check_fee;
public:
    Checking_Account(std::string name = def_name, double balance = def_balance, double per_check_fee = def_per_check_fee);    
    virtual bool withdraw(double amount) override;
    virtual bool deposit(double amount) override;
    virtual ~Checking_Account() = default; // virtual destructor
};

#endif // _CHECKING_ACCOUNT_H_
