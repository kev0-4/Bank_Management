/*
#include <vector>     // For managing collections of accounts
#include <fstream>    // For reading and writing to a CSV file
#include <ctime>      // For handling date and time
*/

#include <bits/stdc++.h>
using namespace std;

// Class Serves as base level for all account types
class BankAccount
{
protected:
    int account_number;
    string account_type;
    double account_balance;
    vector<string> transaction_history;

public:
    BankAccount(int acc_num, const string &acc_type, double initial_balance); // Constructor

    virtual void Deposit(double amount)
    {
        if (amount > 0)
        {
            account_balance += amount;
            transaction_history.push_back("Deposit: " + to_string(amount));
        }
    }
    virtual bool Withdraw(double amount)
    {
        if (account_balance >= amount && amount > 0)
        {
            account_balance -= amount;
            transaction_history.push_back("Withdrawal: " + to_string(amount));
            return true;
        }
        return false; // Transaction fails if insufficient funds or invalid amount
    }
    virtual void Display() const
    {
        cout << "Account Number: " << account_number << endl;
        cout << "Account type: " << account_type << endl;
        cout << "Transaction History: " << endl;
        for (const auto &transaction : transaction_history)
            cout << "-" << transaction << endl;
    }
    double Get_Balance() const
    {
        return account_balance;
    }
    friend ostream &operator<<(ostream &os, const BankAccount &account)
    {
        // os represents output
        // when cout << account is called
        // it will print all 3 parameters making it convinent
        os << "Account NUmber: " << account.account_number << endl;
        os << "Account Type: " << account.account_type << endl;
        os << "Balance: " << account.account_balance << endl;
    }
};

// Special derived Classes
class SavingsAccount : public BankAccount
{
public:
    SavingsAccount(int acc_num, double initial_balance) : BankAccount(acc_num, "Savings", initial_balance), Interest_Rate(Interest_Rate) {}
    void Calculate_Interest()
    {
        // Time_t now = time(nullptr); //implement a structure for time
    }

private:
    double Interest_Rate;
};

class CheckingAccount : public BankAccount
{
public:
    CheckingAccount(int acc_num, double initial_balance);
};

class FixedDepositAccount : public BankAccount
{
public:
    FixedDepositAccount(int acc_num, double initial_balance);
    // Add Maturity date handiling
};

// Functions to 1. Read 2. Write to csv files
// Function to withdraw money
// Function to Log Transactions with details like date, time, type, amount etc
// Use operator overloading to transfer money between accounts
// Friend function to secure money transfer between two accounts (kinda extra)
// Display menu function