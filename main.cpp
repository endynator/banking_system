#include "account.h"
#include "utils.h"
#include <iostream>
#include <string>

BankAccount* LogIn() {
    int num;
    string pw;

    std::cout << "Account number: "; cin >> num;
    std::cout << "Account password: ";
    std::cin.ignore();
    std::getline(std::cin, pw);

    for (auto& acc : accounts) {
        if (acc.accountNumber == num && acc.accountPassword == pw) {
            cout << "Logged in succesfully.\n";

            return &acc;
        }
    }
    std::cout << "Incorrect account number or password.\n";
    return nullptr;
}

void createAccount() {
    bool ifPass = false;
    std::string pw;
    BankAccount account;
    account.accountNumber = generateAccountNumber();
    std::cout << "Enter the account holder's name: ";
    std::cin.ignore();
    std::getline(std::cin, account.accountHolder);
    while (!ifPass) {
        std::cout << "Create a password: ";
        std::cin >> pw;
        ifPass = isStrongPassword(pw);
    }
    account.accountPassword = pw;
    account.balance = 0.0;
    accounts.push_back(account);
    std::cout << "Account created successfully with account number " << account.accountNumber << std::endl;
    init(account);
}

void loop() {
    int choice;
    BankAccount* userAccount = nullptr;
    while (true) {
        std::cout << "(1) Create an account. (2) Log in account. (3) Exit.\n"; cin >> choice;
        if (choice == 1) {
            createAccount();
            break;
        }
        else if (choice == 2) {
            userAccount = LogIn();
            if (userAccount != nullptr) {
                break;
            }
        }
        else {
            return;
        }
    }
    if (userAccount != nullptr) {
        init(*userAccount);
    }
}

int main() {

    loadAccounts();
    loop();

    return 0;
}