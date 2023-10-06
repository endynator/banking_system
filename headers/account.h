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

    /*bool operator==(const BankAccount& rhs) const {
        return accountNumber == rhs.accountNumber && accountPassword == rhs.accountPassword;
    }*/
};

struct Log {
    int accountNumber;
    std::string dateTime;
    std::string action;
    double balance;
    double afterBalance;
    int recipientAccountNumber; 
};

extern std::vector<BankAccount> accounts;
//extern declares a variable without defining it
extern std::vector<Log> Logs;

const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string upd = "\033[0m";

void init(BankAccount& account);
void displayAccountInfo(const BankAccount& account);
void deposit(BankAccount& account);
void withdraw(BankAccount& account);
void loadAccounts();
void saveAccounts();

#endif
