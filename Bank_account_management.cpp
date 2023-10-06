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
class SavingsAccount : public BankAccount{
public:
    SavingsAccount(int Acc_Num, double Initial_Balance);
    // -- add interest calculation functions here --
};
