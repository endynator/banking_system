#include "../headers/account.h"
#include "../headers/utils.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

BankAccount* LogIn() {
	int num = -1;
	string pw;

	std::cout << "Account number: "; cin >> num;
	bool it = std::any_of(accounts.begin(), accounts.end(), [num](const BankAccount& account) {
		return account.accountNumber == num;
		});
	if (!it) { 
		std::cout << red << "Account wasn't found." << upd << endl; 
		system("cls");
		return nullptr;
	}

	std::cout << "Account password: ";
	std::cin.ignore();
	std::getline(std::cin, pw);

	for (auto& acc : accounts) {
		if (acc.accountNumber == num && acc.accountPassword == pw) {
			system("cls");
			std::cout << green << "Logged in succesfully." << upd << std::endl;

			return &acc;
		}
	}
	system("cls");
	std::cout << red << "Incorrect account number or password." << upd << std::endl;
	return nullptr;
}

void createAccount() {
	bool ifPass = false;
	std::string pw;
	BankAccount account;
	account.accountNumber = 1000 + accounts.size();
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
	system("cls");
	std::cout << green << "Account created successfully with account number " << account.accountNumber << upd << std::endl;
	init(accounts.back());
}

void loop() {
	int choice;
	BankAccount* userAccount = nullptr;
	while (true) {
		std::cout << "Welcome to the Banking System\nIt's a simulation of a bank, located on your local machine\nPlease, choose the option:\n(1) Create an account.\n(2) Log in account.\n(3) Exit.\n"; cin >> choice;
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
	system("cls");
	loadAccounts();
	loop();

	return 0;
}
