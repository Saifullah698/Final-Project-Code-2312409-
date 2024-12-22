#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;

// Utility Function for Timestamp
string getCurrentTimestamp() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

// Class: Transaction
class Transaction {
private:
    int transactionID;
    string type;
    float amount;
    string currency;
    string timestamp;

public:
    Transaction(int id, string t, float a, string c)
        : transactionID(id), type(t), amount(a), currency(c), timestamp(getCurrentTimestamp()) {}

    void displayTransaction() const {
        cout << "Transaction ID: " << transactionID
             << " | Type: " << type
             << " | Amount: " << amount
             << " " << currency
             << " | Timestamp: " << timestamp;
        cout << endl;
    }
};

// Class: CurrencyConverter
class CurrencyConverter {
private:
    map<string, float> rates;

public:
    CurrencyConverter() {
        rates["USD"] = 1.0;
        rates["EUR"] = 0.93;
        rates["GBP"] = 0.82;
    }

    float convert(float amount, string from, string to) {
        if (rates.find(from) == rates.end() || rates.find(to) == rates.end()) {
            cout << "Invalid currency." << endl;
            return 0;
        }
        return (amount / rates[from]) * rates[to];
    }

    void displayRates() {
        for (auto& rate : rates) {
            cout << rate.first << ": " << rate.second << endl;
        }
    }
};

// Class: Account
class Account {
private:
    int pin;
    float balance;
    vector<Transaction> transactionHistory;

public:
    Account(int p, float b) : pin(p), balance(b) {}

    bool validatePIN(int enteredPIN) {
        return enteredPIN == pin;
    }

    void updateBalance(float amount) {
        balance += amount;
    }

    float getBalance() {
        return balance;
    }

    void addTransaction(int id, string type, float amount, string currency) {
        transactionHistory.emplace_back(id, type, amount, currency);
    }

    void viewTransactions() {
        cout << "Transaction History:" << endl;
        for (const auto& txn : transactionHistory) {
            txn.displayTransaction();
        }
    }
};

// Class: ATM
class ATM {
private:
    CurrencyConverter converter;

public:
    void withdraw(Account& account, float amount) {
        if (account.getBalance() < amount) {
            cout << "Insufficient funds." << endl;
        } else {
            account.updateBalance(-amount);
            account.addTransaction(account.getBalance(), "Withdrawal", amount, "USD");
            cout << "Withdrawal successful." << endl;
        }
    }

    void deposit(Account& account, float amount) {
        account.updateBalance(amount);
        account.addTransaction(account.getBalance(), "Deposit", amount, "USD");
        cout << "Deposit successful." << endl;
    }

    void showMenu() {
        cout << "1. Withdraw\n2. Deposit\n3. Check Balance\n4. View Transactions\n5. Exchange Rates\n6. Exit" << endl;
    }

    void handleMenu(Account& account) {
        int choice;
        do {
            showMenu();
            cout << "Choose an option: ";
            cin >> choice;
            switch (choice) {
            case 1: {
                float amount;
                cout << "Enter amount: ";
                cin >> amount;
                withdraw(account, amount);
                break;
            }
            case 2: {
                float amount;
                cout << "Enter amount: ";
                cin >> amount;
                deposit(account, amount);
                break;
            }
            case 3:
                cout << "Balance: " << account.getBalance() << endl;
                break;
            case 4:
                account.viewTransactions();
                break;
            case 5:
                converter.displayRates();
                break;
            case 6:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != 6);
    }
};

int main() {
    Account user(1234, 1000.0);
    ATM atm;

    int pin;
    cout << "Enter PIN: ";
    cin >> pin;

    if (user.validatePIN(pin)) {
        atm.handleMenu(user);
    } else {
        cout << "Invalid PIN." << endl;
    }

    return 0;
}
