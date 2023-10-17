# ***Bank Account Management System***
# ***Introduction***
This is a simple Bank Account Management System implemented in C++ that allows users to create and manage different types of bank 
accounts, including Savings, Checking, and Fixed Deposit accounts. Users can perform various operations such as creating an account, 
making deposits, making withdrawals, displaying account information, and calculating interest for Savings accounts. The system also 
supports reading and writing account data to a CSV file for persistence.


# ***Prerequisites***


To run this program, you will need a C++ development environment that supports the required libraries:

![Alt](path to img)

Ensure that your development environment includes these libraries.


# ***Getting Started***

Download or clone the repository to your local machine.<br>
Open the C++ source code in your preferred development environment.<br>
Ensure that the required libraries are available in your environment (as mentioned in the #include statements).<br>
Compile and run the program.

# ***Usage***


Once you have compiled and run the program, you will be presented with a menu to perform various actions:
1.	Create Account: Create a new bank account. You'll be asked for the account number, account type (Savings, Checking, or Fixed_Deposit), and the initial balance. Additional information such as interest rate or maturity date is required based on the account type.
2.	Deposit: Make a deposit into an existing account. You'll need to enter the account number and the deposit amount.
3.	Withdraw: Make a withdrawal from an existing account. Enter the account number and the withdrawal amount. Note that Fixed Deposit accounts may have restrictions on withdrawals.
4.	Display Account Info: View the details and transaction history of an existing account. You'll need to provide the account number.
5.	Calculate Interest (Savings Account): Calculate and add interest to all Savings accounts. This option is only applicable to Savings accounts.
6.	Exit: Exit the program.



# ***Data Persistence***

Account data is stored in a CSV file named accounts.csv. This allows the system to load existing account information when the program is run and save account data when new accounts or transactions are added.

# ***Account Types***

The system supports the following types of accounts:<br>
•	Savings Account: Allows you to specify an interest rate and calculate interest.<br>
•	Checking Account: A standard checking account with no additional features.<br>
•	Fixed Deposit Account: Requires specifying a maturity date. Withdrawals may be restricted before the maturity date.
