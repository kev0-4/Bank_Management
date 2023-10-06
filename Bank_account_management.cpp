#include <bits/stdc++.h>
using namespace std;

// Class Serves as base level for all account types
class BankAccount
{
protected:
    int Account_Number;
    string Account_Type;
    double Account_Balance;
    vector<string> Transaction_History;

public:
    BankAccount(int Acc_Num, const string &Acc_Type, double Initial_Balance);

    virtual void Deposit(double Amount);
    virtual bool Withdraw(double Amount);
    virtual void Display() const;
    double Get_Balance() const;
};

// Special derived Classes
class SavingsAccount : public BankAccount
{
public:
    SavingsAccount(int Acc_Num, double Initial_Balance);
    void Calculate_Interest();

private:
    double Interest_Rate;
};

class CheckingAccount : public BankAccount
{
public:
    CheckingAccount(int Acc_Num, double Initial_Balance);
};

class FixedDepositAccount : public BankAccount
{
public:
    FixedDepositAccount(int Acc_Num, double Initial_Balance);
    // Add Maturity date handiling
};

// Functions to 1. Read 2. Write to csv files
// Function to withdraw money
// Function to Log Transactions with details like date, time, type, amount etc
// Use operator overloading to transfer money between accounts
// Friend function to secure money transfer between two accounts (kinda extra)
// Display menu function 