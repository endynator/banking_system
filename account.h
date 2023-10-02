#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>

using namespace std;

struct BankAccount {
    int accountNumber;
    std::string accountPassword;
    std::string accountHolder; //a.k.a Name
    double balance;

    // Add this operator overload inside the struct to avoid an error
    bool operator==(const BankAccount& rhs) const {
        return accountNumber == rhs.accountNumber && accountPassword == rhs.accountPassword;
    }
};

struct Log {
    int accountNumber;
    std::string dateTime;
    std::string action;
    double balance;
    double afterBalance;
    int recipientAccountNumber; // Reciever
};


extern std::vector<BankAccount> accounts; 
//extern declares a variable without defining it
extern std::vector<Log> Logs;

void init(BankAccount& account);
void displayAccountInfo(const BankAccount& account);
void deposit(BankAccount& account);
void withdraw(BankAccount& account);
void loadAccounts();
void saveAccounts();

#endif
