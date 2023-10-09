#include <vector>  // For managing collections of accounts
#include <fstream> // For reading and writing to a CSV file
#include <ctime>   // For handling date and time

#include <bits/stdc++.h> // Without other libraries it is givng error

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
    BankAccount(int acc_num, const string &acc_type, double initial_balance)
        : account_number(acc_num), account_type(acc_type), account_balance(initial_balance) {} // Constructor

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
    double Get_Balance() const // needed to declare constant else qualifiers not compatible error
    {
        return account_balance;
    }
    int Get_account_number() const
    {
        return account_number;
    }
    string Get_account_type() const
    {
        return account_type;
    }
    virtual string GetAdditionalData() const
    {
        return ""; // Default implementation returns an empty string
    }

    bool TransferMoney(BankAccount &source, BankAccount &destination, double amount)
    {
        if (source.Withdraw(amount))
        {
            destination.Deposit(amount);
            cout << "Money transferred successfully." << endl;
            return true;
        }
        else
        {
            cout << "Money transfer failed. Insufficient funds in the source account." << endl;
            return false;
        }
    }

    virtual void Calculate_Interest() {}

    friend ostream &operator<<(ostream &os, const BankAccount &account)
    {
        // os represents output
        // when cout << account is called
        // it will print all 3 parameters making it convinent
        os << "Account NUmber: " << account.account_number << endl;
        os << "Account Type: " << account.account_type << endl;
        os << "Balance: " << account.account_balance << endl;
    }
    void record_transaction(const string &type, double amount)
    {
        /*
        this record is logged to transaction history with date and time
        time_t tm* are inbuilt dt to store time data , similar to python date and time
        time_t represents time as int
        tm* is time structure
        */
        time_t now = time(nullptr);      // get curr time in seconds
        tm *localTime = localtime(&now); // converts time_t to a structure with date and time
        int days_in_month = 30;          // assumption for simplicity
        // logging in transaction history
        char timestamp[40];
        // strftime - string format time to 'more' human redable string
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);
        string transaction_details = "[" + std::string(timestamp) + "] " + type + ": $" + std::to_string(amount);
        transaction_history.push_back(transaction_details);
    }
};

// Special derived Classes
class SavingsAccount : public BankAccount
{
private:
    double interest_rate;

public:
    /*
    Member Variables
    acc_num,acc_type,acc_balance
    transaction_history - vector of string that log all transaction made
    interest_rate
    */
    SavingsAccount(int acc_num, double initial_balance, double interest_rate) : BankAccount(acc_num, "Savings", initial_balance), interest_rate(interest_rate) {}

    void Calculate_Interest()
    {
        /*
        Function checks initial balance and interesr rate and then calculates interest earned
        over specific period of time
        Then interest is added to account's balance
        */
        double interest = (account_balance * interest_rate) / 100.0;
        account_balance += interest;
        record_transaction("Interest Credited", interest);
    }
    string GetAdditionalData() const override
    {
        return to_string(interest_rate); // Additional data for SavingsAccount
    }
};

class FixedDepositAccount : public BankAccount
{
private:
    tm maturity_date; // date when fixed deposit will mature
public:
    FixedDepositAccount(int acc_num, double initial_balance, const tm &maturity_date)
        : BankAccount(acc_num, "Fixed Deposit", initial_balance), maturity_date(maturity_date){};

    bool Withdraw(double amount) override
    { // ovveride keyword is to clarify that this will override virtual function
        // Calculate the current time
        time_t now = time(0);
        tm *currentTime = localtime(&now);

        // calculate the time difference in seconds
        /*
        difftime calculates differene in seconds two time_t and return a double
        mktime converts tm to time_t, used when mathematical operations needed to be performed
        */
        double timeDifference = difftime(mktime(currentTime), mktime(&maturity_date));

        if (timeDifference >= 0)
            return BankAccount ::Withdraw(amount);
        else
        {
            cout << "Withdrawal from Fixed Deposit account is not allowed before maturity date." << endl;
            return false;
        }
    }

    void Display() const override
    {
        // + 1900 cause it counts from start of time
        BankAccount::Display();
        cout << "Maturity Date: " << maturity_date.tm_year + 1900
             << "-" << maturity_date.tm_mon + 1 << "-"
             << maturity_date.tm_mday << std::endl;
    }
    string GetAdditionalData() const override
    {
        return to_string(maturity_date.tm_year + 1900) + "-" + to_string(maturity_date.tm_mon + 1) + "-" + to_string(maturity_date.tm_mday);
    }
};

class CheckingAccount : public BankAccount
{
public:
    CheckingAccount(int acc_num, double initial_balance)
        : BankAccount(acc_num, "Checking", initial_balance) {}
};

void writeAccountsToCSV(const vector<BankAccount> &accounts)
{
    ofstream file("accounts.csv");
    if (!file.is_open())
        return;

    for (const BankAccount &account : accounts)
    {
        file << fixed << setprecision(2);
        file << account.Get_account_number() << "," << account.Get_Balance() << "," << account.Get_account_type();

        string additionalData = account.GetAdditionalData();
        if (!additionalData.empty())
            file << "," << additionalData;

        file << "\n";
    }

    file.close();
}

void readAccountsFromCSV(vector<BankAccount> &accounts)
{
    ifstream file("accounts.csv");
    if (!file.is_open())
        return;
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        double account_balance;
        int account_number;
        string account_type;

        if (iss >> account_balance >> account_number >> account_type)
        {
            if (account_type == "Savings")
            {
                double interest_rate;
                // reading interest rate from csv;
                accounts.push_back(SavingsAccount(account_number, account_balance, interest_rate));
            }
            else if (account_type == "Checking")
            {
                accounts.push_back(CheckingAccount(account_number, account_balance));
            }
            else if (account_type == "Fixed Deposit")
            {
                int year, month, day;
                iss >> year >> month >> day;
                tm maturity_date = {0};
                // tm has tm_year, tm_month etc etc
                maturity_date.tm_year = year - 1900; // same start of time thing
                maturity_date.tm_mon = month - 1;
                maturity_date.tm_mday = day;
                accounts.push_back(FixedDepositAccount(account_number, account_balance, maturity_date));
            }
        }
    }
    file.close();
}

int main()
{

    vector<BankAccount> accounts;

    // Read account data from CSV file
    readAccountsFromCSV(accounts);

    int choice;
    while (true)
    {
        cout << "Bank Account Management System" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Display Account Info" << endl;
        cout << "5. Calculate Interest (Savings Account)" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int accountNumber;
            string accountType;
            double initialBalance;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter account type (Savings, Checking, Fixed_Deposit, etc.): ";
            // scanf(" %[^\n]s",accountType);
            cin >> accountType;
            cout << "Enter initial balance: ";
            cin >> initialBalance;

            if (accountType == "Savings")
            {
                double interestRate;
                cout << "Enter interest rate: ";
                cin >> interestRate;
                accounts.push_back(SavingsAccount(accountNumber, initialBalance, interestRate));
            }
            else if (accountType == "Checking")
            {
                accounts.push_back(CheckingAccount(accountNumber, initialBalance));
            }
            else if (accountType == "Fixed_Deposit")
            {
                int year, month, day;
                cout << "Enter maturity year: ";
                cin >> year;
                cout << "Enter maturity month: ";
                cin >> month;
                cout << "Enter maturity day: ";
                cin >> day;

                tm maturityDate = {0};
                maturityDate.tm_year = year - 1900;
                maturityDate.tm_mon = month - 1;
                maturityDate.tm_mday = day;

                accounts.push_back(FixedDepositAccount(accountNumber, initialBalance, maturityDate));
            }
            else
            {
                cout << "Invalid account type. Please try again." << endl;
            }

            writeAccountsToCSV(accounts);
            break;
        }

        case 2:
        {
            int accountNumber;
            double amount;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter deposit amount: ";
            cin >> amount;

            for (BankAccount &account : accounts)
            {
                if (accountNumber == account.Get_account_number())
                {
                    account.Deposit(amount);
                    writeAccountsToCSV(accounts);
                    break;
                }
            }
            break;
        }
        case 3:
        {
            int accountNumber;
            double amount;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter Withdrawal amount: ";
            cin >> amount;

            for (BankAccount &account : accounts)
            {
                if (accountNumber == account.Get_account_number())
                {
                    if (account.Withdraw(amount))
                    {
                        cout << "Withdrawal successful." << endl;
                        writeAccountsToCSV(accounts);
                    }
                    else
                    {
                        cout << "Insufficient funds." << endl;
                    }
                    break;
                }
            }
            break;
        }
        case 4:
        {
            int accountNumber;
            cout << "Enter account number: ";
            cin >> accountNumber;

            for (const BankAccount &account : accounts)
            {
                if (accountNumber == account.Get_account_number())
                {
                    account.Display();
                    break;
                }
            }
            break;
        }
        case 5:
        {
            // Calculate interest for all savings accounts
            for (BankAccount &account : accounts)
            {
                account.Calculate_Interest();
                writeAccountsToCSV(accounts);
            }
            break;
        }
        case 6:
        {
            // Exit the program
            return 0;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
