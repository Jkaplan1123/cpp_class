#ifndef _TRUST_ACCOUNT_H_
#define _TRUST_ACCOUNT_H_
#include <iostream>
#include <string>
#include "Savings_Account.h"

class Trust_Account : public Savings_Account {
    friend std::ostream &operator<<(std::ostream &os, const Trust_Account &account);
private:

    // Same as Savings_Account
    static constexpr const char *def_name = "Unnamed Trust Account";
    static constexpr double def_balance = 0;
    static constexpr double def_int_rate = 0.0;

    // Unique to Trust Class
    static constexpr double def_max_withdrawl_percentage = 20.0;
    static const unsigned int def_maximum_annual_withdrawals = 3;
    static constexpr double def_deposit_bonus_threshold = 5000.0;
    static constexpr double def_deposit_bonus_amount = 50.0;

protected:
    double max_withdraw_percentage;
    int max_annual_withdrawals;
    double deposit_bonus_threshold;
    double deposit_bonus_amount;
    int current_withdrawals;
public:
    Trust_Account(std::string name = def_name, double balance = def_balance, double int_rate = def_int_rate,
        double max_withdraw_percentage = def_max_withdrawl_percentage, int max_annual_withdrawals = def_maximum_annual_withdrawals,
        double deposit_bonus_threshold = def_deposit_bonus_threshold, double deposit_bonus_amount = def_deposit_bonus_amount,
        int current_withdrawals = 0);
    // Account(std::string name = "Unamed Account", double balance = 0.0);
    bool deposit(double amount);
    bool withdraw(double amount);

    int withdrawals_used() const; // returns the number of withdrawls used this year
    int withdrawals_remaining() const; // returns the number of withdrawls reamining this year
};

#endif