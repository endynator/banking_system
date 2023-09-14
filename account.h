#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>

using namespace std;

struct BankAccount {
    int accountNumber;
    std::string accountPassword;
    std::string accountHolder;
    double balance;

    // Add this operator overload inside the BankAccount struct in 'account.h' to avoid an error
    bool operator==(const BankAccount& rhs) const {
        return accountNumber == rhs.accountNumber && accountPassword == rhs.accountPassword;
    }
};

extern std::vector<BankAccount> accounts;

void init(BankAccount& account);
void createAccount();
void displayAccountInfo(const BankAccount& account);
void deposit(BankAccount& account);
void withdraw(BankAccount& account);
void listAllAccounts();
void loadAccounts();
void saveAccounts();
BankAccount* LogIn();

#endif
