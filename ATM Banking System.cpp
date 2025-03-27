#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct Account {
    int accountNumber;
    string name;
    double balance;
};

void loadAccounts(Account accounts[], int &numAccounts) {
    ifstream infile("accounts.txt");
    numAccounts = 0;
    while (infile >> accounts[numAccounts].accountNumber >> accounts[numAccounts].name >> accounts[numAccounts].balance) {
        numAccounts++;
    }
    infile.close();
}

void saveAccounts(Account accounts[], int numAccounts) {
    ofstream outfile("accounts.txt");
    for (int i = 0; i < numAccounts; i++) {
        outfile << accounts[i].accountNumber << " " << accounts[i].name << " " << accounts[i].balance << endl;
    }
    outfile.close();
}

int findAccount(Account accounts[], int numAccounts, int accountNumber) {
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}

void deposit(Account &account, double amount) {
    if (amount > 0) {
        account.balance += amount;
        cout << endl << "Deposit successful. New balance: " << account.balance << endl;
    } else {
        cout << endl << "Invalid deposit amount." << endl;
    }
}

void withdraw(Account &account, double amount) {

    if (amount > 0 && amount <= account.balance) {
        account.balance -= amount;
        cout << endl << "Withdrawal successful. New balance: " << account.balance << endl;
    } else {
        cout << endl << "Invalid withdrawal amount or insufficient balance." << endl;
    }
}

void displayBalance(const Account &account) {
    cout << endl << "Account Holder's Name: " << account.name<< endl;
    cout << "Account balance: " << account.balance << endl << endl;
}

int main() {
    Account accounts[20];
    int numAccounts = 0;
    loadAccounts(accounts, numAccounts);

    int choice, accountNumber;
    double amount;
    while (true) {
        cout << endl << "ATM Account System" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display Balance" << endl;
        cout << "4. Exit" << endl;
        cout << endl << "Enter your choice: ";
        cin >> choice;

        if (choice == 4) {
            // we just saved it one more time to be sure that it is actually saved
            cout << endl << "Thank you for using our Banking System!!!!" << endl;
            saveAccounts(accounts, numAccounts);
            break;
        }

        cout << endl << "Enter account number: ";
        cin >> accountNumber;
        int index = findAccount(accounts, numAccounts, accountNumber);
        if (index == -1) {
            cout << "Account not found." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                cout << endl << "Account Holder's Name: " << accounts[index].name << endl;
                cout << endl << "Enter amount to deposit: ";
                cin >> amount;
                deposit(accounts[index], amount);
                saveAccounts(accounts, numAccounts);
                break;
            case 2:
                cout << endl << "Account Holder's Name: " << accounts[index].name << endl;
                cout << endl << "Enter amount to withdraw: ";
                cin >> amount;
                withdraw(accounts[index], amount);
                saveAccounts(accounts, numAccounts);
                break;
            case 3:
                displayBalance(accounts[index]);
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }

    return 0;
}