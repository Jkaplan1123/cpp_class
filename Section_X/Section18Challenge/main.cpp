#include <iostream>
#include <memory>
#include "Account.h"
#include "Checking_Account.h"
#include "Savings_Account.h"
#include "Trust_Account.h"
// #include "Account_Util.h"

using namespace std;

void illegalbalancetext(std::string act_name){
    cout << "Account \"" << act_name << "\" could not be created due to an illegal balance." << endl;
}

void insufficient_funds_text(Account &act, double withdraw_amount){
    cout << "$" << withdraw_amount << " could not be withdrawn from \"" << act.get_name()<< "\" due to insufficient funds." << endl;
    cout << "\"" << act.get_name() << "\" currently has a balance of $" << act.get_balance() << endl; 
}

void successful_withdrawl(Account &act, double withdraw_amount){
    cout << "$" << withdraw_amount << " successfully withdrawn from \"" << act.get_name()<< "\"." << endl;
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
    
    // Test Illegal Withdrawal Exceptions

    {
        double starting_balance = 100;
        Checking_Account checking {"Checking", starting_balance};
        Savings_Account saving {"Savings", starting_balance};
        Trust_Account trust {"Trust", starting_balance}; // Note to self: trust accounts are allowed a maximum of 3 withdrawals. No withdrawal from a Trust account can exceed 20% of the balance
        
        double balance_modifier {};
        cout << "Insert a number below to modify the withdrawal ammount" << endl;
        cout << "Insert a positive number to withdraw more than the allowed amount (should throw an exception)" << endl;
        cout << "Insert a zero or a negative number to withdraw an allowed amount (should succeed)" << endl;
        cout << " --------------------------------------------- " << endl;
        cout << "Insert Number: ";
        cin >> balance_modifier;
        
        double withdraw_amount {checking.get_balance() + balance_modifier};

        try{
            checking.withdraw(withdraw_amount);
            successful_withdrawl(checking, withdraw_amount);
        }
        catch(InsufficientFundsException){
            insufficient_funds_text(checking, withdraw_amount);
        }

        try{
            saving.withdraw(withdraw_amount);
            successful_withdrawl(saving, withdraw_amount);
        }
        catch(InsufficientFundsException){
            insufficient_funds_text(saving, withdraw_amount);
        }

        // Special Testing for Trust

        withdraw_amount = 0.5 * trust.get_balance();
        try{
            trust.withdraw(withdraw_amount);
            successful_withdrawl(trust, withdraw_amount);
        }
        catch(InsufficientFundsException){
            insufficient_funds_text(trust, withdraw_amount);
        }
        catch(IllegalTrustWithdrawalException){
            cout << "Could not withdraw $" << withdraw_amount << "from \"" << trust.get_name() << " due to limitations on the trust account." << endl;
        }
        

        for (int i = 0; i < 4; i++){
            withdraw_amount = 0.1 * trust.get_balance();
            try{
                trust.withdraw(withdraw_amount);
                successful_withdrawl(trust, withdraw_amount);
            }
            catch(InsufficientFundsException){
                insufficient_funds_text(trust, withdraw_amount);
            }
            catch(IllegalTrustWithdrawalException){
                cout << "Could not withdraw $" << withdraw_amount << " from \"" << trust.get_name() << " due to limitations on the trust account." << endl;
            }
        }
    }

    std::cout << "Program completed successfully" << std::endl;
    return 0;
}

