#include "account.h"
#include "utils.h"
#include <iostream>
#include <string>

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