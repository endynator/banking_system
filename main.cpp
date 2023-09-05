#include "account.h"
#include "utils.h"
#include <iostream>
#include <string>

int main() {
    int choice;
    BankAccount* userAccount = nullptr;
    loadAccounts(); 

    while (true) {
        std::cout << "(1) Create an account. (2) Log in account.\n"; cin >> choice;
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
    }
    if (userAccount != nullptr) {
        init(*userAccount);
    }
    return 0;
}
