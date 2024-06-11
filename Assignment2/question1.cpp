#include <iostream>
#include <cstring>

const int MAX_TRANSACTIONS = 100;
const int MAX_LOANS = 10;
const int MAX_ACCOUNTS = 100;

class Transaction {
public:
    char date[11]; // Format: YYYY-MM-DD
    double amount;
    char type[10];

    Transaction() : amount(0) {
        std::strcpy(date, "");
        std::strcpy(type, "");
    }

    Transaction(const char* date, double amount, const char* type) : amount(amount) {
        std::strcpy(this->date, date);
        std::strcpy(this->type, type);
    }
};

class Loan {
public:
    char date[11]; // Format: YYYY-MM-DD
    double amount;

    Loan() : amount(0) {
        std::strcpy(date, "");
    }

    Loan(const char* date, double amount) : amount(amount) {
        std::strcpy(this->date, date);
    }
};

class Account {
protected:
    int accountNumber;
    char holderName[100];
    char address[200];
    char accountType[10];
    double funds;
    Transaction transactionHistory[MAX_TRANSACTIONS];
    Loan loanHistory[MAX_LOANS];
    int transactionCount;
    int loanCount;

public:
    Account(int accNum, const char* name, const char* addr, const char* type, double fund)
        : accountNumber(accNum), funds(fund), transactionCount(0), loanCount(0) {
        std::strcpy(holderName, name);
        std::strcpy(address, addr);
        std::strcpy(accountType, type);
    }

    virtual void deposit(double amount) {
        funds += amount;
        if (transactionCount < MAX_TRANSACTIONS) {
            transactionHistory[transactionCount++] = Transaction("2024-05-25", amount, "Deposit");
        }
    }

    virtual void withdraw(double amount) {
        if (amount > funds) {
            std::cout << "Insufficient funds\n";
            return;
        }
        funds -= amount;
        if (transactionCount < MAX_TRANSACTIONS) {
            transactionHistory[transactionCount++] = Transaction("2024-05-25", amount, "Withdraw");
        }
    }

    virtual void updateInfo(const char* name, const char* addr) {
        std::strcpy(holderName, name);
        std::strcpy(address, addr);
    }

    virtual void viewPassbook() const {
        std::cout << "Passbook for account number: " << accountNumber << "\n";
        for (int i = 0; i < transactionCount; ++i) {
            std::cout << "Date: " << transactionHistory[i].date
                      << " Amount: " << transactionHistory[i].amount
                      << " Type: " << transactionHistory[i].type << "\n";
        }
    }

    virtual void applyForLoan(double amount) {
        if (loanCount < MAX_LOANS) {
            loanHistory[loanCount++] = Loan("2024-05-25", amount);
        } else {
            std::cout << "Maximum loan limit reached\n";
        }
    }

    virtual void searchTransaction(const char* date, double amount) const {
        for (int i = 0; i < transactionCount; ++i) {
            if (std::strcmp(transactionHistory[i].date, date) == 0 &&
                transactionHistory[i].amount == amount) {
                std::cout << "Transaction found: " << "Date: " << transactionHistory[i].date
                          << " Amount: " << transactionHistory[i].amount
                          << " Type: " << transactionHistory[i].type << "\n";
                return;
            }
        }
        std::cout << "Transaction not found\n";
    }

    double getFunds() const {
        return funds;
    }

    void setFunds(double fund) {
        funds = fund;
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

class JointAccount : public Account {
    char secondHolderName[100];
public:
    JointAccount(int accNum, const char* name1, const char* name2, const char* addr, const char* type, double fund)
        : Account(accNum, name1, addr, type, fund) {
        std::strcpy(secondHolderName, name2);
    }

    void updateInfo(const char* name1, const char* name2, const char* addr) {
        std::strcpy(holderName, name1);
        std::strcpy(secondHolderName, name2);
        std::strcpy(address, addr);
    }

    void viewPassbook() const override {
        std::cout << "Passbook for joint account number: " << accountNumber << "\n";
        std::cout << "Account Holder 1: " << holderName << "\n";
        std::cout << "Account Holder 2: " << secondHolderName << "\n";
        for (int i = 0; i < transactionCount; ++i) {
            std::cout << "Date: " << transactionHistory[i].date
                      << " Amount: " << transactionHistory[i].amount
                      << " Type: " << transactionHistory[i].type << "\n";
        }
    }
};

class Bank {
private:
    Account* accounts[MAX_ACCOUNTS];
    int accountCount;

public:
    Bank() : accountCount(0) {}

    void createAccount(int accNum, const char* name, const char* addr, const char* type, double fund) {
        if (accountCount < MAX_ACCOUNTS) {
            accounts[accountCount++] = new Account(accNum, name, addr, type, fund);
        } else {
            std::cout << "Maximum account limit reached\n";
        }
    }

    void createJointAccount(int accNum, const char* name1, const char* name2, const char* addr, const char* type, double fund) {
        if (accountCount < MAX_ACCOUNTS) {
            accounts[accountCount++] = new JointAccount(accNum, name1, name2, addr, type, fund);
        } else {
            std::cout << "Maximum account limit reached\n";
        }
    }

    Account* getAccount(int accNum) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i]->getAccountNumber() == accNum) {
                return accounts[i];
            }
        }
        return nullptr;
    }

    void deleteAccount(int accNum) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i]->getAccountNumber() == accNum) {
                delete accounts[i];
                accounts[i] = accounts[--accountCount];
                return;
            }
        }
        std::cout << "Account not found\n";
    }

    void transferFunds(int fromAccNum, int toAccNum, double amount) {
        Account* fromAccount = getAccount(fromAccNum);
        Account* toAccount = getAccount(toAccNum);

        if (fromAccount && toAccount) {
            if (fromAccount->getFunds() >= amount) {
                fromAccount->withdraw(amount);
                toAccount->deposit(amount);
            } else {
                std::cout << "Insufficient funds in the source account\n";
            }
        } else {
            std::cout << "One or both accounts not found\n";
        }
    }
};

int main() {
    Bank bank;
    bank.createAccount(1001, "John Doe", "123 Elm St", "Savings", 1000.0);
    bank.createJointAccount(1002, "Jane Doe", "Jim Doe", "456 Oak St", "Joint", 2000.0);

    Account* acc1 = bank.getAccount(1001);
    Account* acc2 = bank.getAccount(1002);

    if (acc1) {
        acc1->deposit(500.0);
        acc1->withdraw(200.0);
        acc1->viewPassbook();
        acc1->searchTransaction("2024-05-25", 500.0);
    }

    if (acc2) {
        acc2->deposit(1000.0);
        acc2->withdraw(300.0);
        acc2->viewPassbook();
        acc2->searchTransaction("2024-05-25", 1000.0);
    }

    bank.transferFunds(1001, 1002, 150.0);

    if (acc1) acc1->viewPassbook();
    if (acc2) acc2->viewPassbook();

    bank.deleteAccount(1001);
    bank.deleteAccount(1002);

    return 0;
}
