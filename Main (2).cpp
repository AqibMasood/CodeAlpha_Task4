#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// ==========================
// Transaction Class
// ==========================
class Transaction {
public:
    string type;
    double amount;
    string date;

    Transaction(string t, double a) {
        type = t;
        amount = a;
        time_t now = time(0);
        date = ctime(&now);
        date.pop_back(); // Remove newline
    }

    void display() const {
        cout << date << " | " << type << " | Amount: $" << amount << endl;
    }
};

// ==========================
// Account Class
// ==========================
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNum, double initialBalance = 0.0) {
        accountNumber = accNum;
        balance = initialBalance;
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposited $" << amount << " successfully." << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
        cout << "Withdrew $" << amount << " successfully." << endl;
        return true;
    }

    bool transfer(Account &to, double amount) {
        if (withdraw(amount)) {
            to.deposit(amount);
            transactions.emplace_back("Transfer to Account " + toString(to.getAccountNumber()), amount);
            return true;
        }
        return false;
    }

    void showTransactions() const {
        cout << "Transaction History for Account " << accountNumber << ":\n";
        for (const auto &t : transactions) {
            t.display();
        }
    }

    static string toString(int num) {
        return to_string(num);
    }
};

// ==========================
// Customer Class
// ==========================
class Customer {
private:
    string name;
    int customerID;
    vector<Account> accounts;

public:
    Customer(string n, int id) {
        name = n;
        customerID = id;
    }

    void addAccount(Account acc) {
        accounts.push_back(acc);
    }

    Account* getAccount(int accNum) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                return &acc;
            }
        }
        return nullptr;
    }

    void displayInfo() const {
        cout << "Customer ID: " << customerID << ", Name: " << name << endl;
        for (const auto &acc : accounts) {
            cout << "  Account " << acc.getAccountNumber() << " | Balance: $" << acc.getBalance() << endl;
        }
    }
};

// ==========================
// Main
// ==========================
int main() {
    Customer c1("Alice", 1);
    Customer c2("Bob", 2);

    Account a1(101, 500.0);
    Account a2(102, 1000.0);

    c1.addAccount(a1);
    c2.addAccount(a2);

    // Deposit and withdraw
    c1.getAccount(101)->deposit(200);
    c1.getAccount(101)->withdraw(100);

    // Transfer funds
    c1.getAccount(101)->transfer(*c2.getAccount(102), 150);

    // Display details
    c1.displayInfo();
    c1.getAccount(101)->showTransactions();

    c2.displayInfo();
    c2.getAccount(102)->showTransactions();

    return 0;
}
