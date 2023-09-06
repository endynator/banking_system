#include "account.h"
#include "utils.h"
#include "main.h"
#include "admin.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

std::vector<BankAccount> accounts;

void init(BankAccount& account) {
	int choice;
	if (account.accountNumber == 0) {
		do{
			displayAdminMenu();
			std::cin >> choice;

			switch (choice) {
			case 1:
				AdminListAllAccounts();
				break;
			case 2:
				AdminDelAccount();
				break;
			case 3:
				AdminChangeBalance();
				break;
			case 4:
				saveAccounts(); // Save accounts to the file before exiting
				std::cout << "Exiting the program.\n";
				return;
			}
		} while (choice >= 1 && choice <= 4);
	}
	do {
		displayMenu();
		std::cin >> choice;

		switch (choice) {
		case 1:
			displayAccountInfo(account);
			break;
		case 2:
			deposit(account);
			break;
		case 3:
			withdraw(account);
			break;
		case 4:
			saveAccounts(); // Save accounts to the file before exiting
			std::cout << "Exiting the program.\n";
			return;
		case 5:
			std::cout << "Logged out successfuly.\n";
			saveAccounts();
			loop();
			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 4 && choice != 5);
}

void createAccount() {
	bool ifPass = false;
	std::string pw;
	BankAccount account;
	account.accountNumber = generateAccountNumber();
	std::cout << "Enter the account holder's name: ";
	std::cin.ignore(); // Consume the newline character left by previous input
	std::getline(std::cin, account.accountHolder);
	while (!ifPass) {
		std::cout << "Create a password: ";
		std::cin >> pw;
		ifPass = isStrongPassword(pw);
	}
	account.accountPassword = pw;
	account.balance = 0.0; // Initialize balance only for new accounts
	accounts.push_back(account);
	std::cout << "Account created successfully with account number " << account.accountNumber << std::endl;
	init(account);
}

void displayAccountInfo(const BankAccount& account) {
	std::string pw;
	std::cout << "Password: ";
	std::cin.ignore(); // Consume the newline character left by previous input
	std::getline(std::cin, pw);

	if (account.accountPassword == pw) {
		std::cout << "Account Number: " << account.accountNumber << std::endl;
		std::cout << "Account Holder: " << account.accountHolder << std::endl;
		std::cout << "Balance: $" << account.balance << std::endl;
		return;
	}

	std::cout << "Incorrect password.\n";
}

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

void deposit(BankAccount& account) {
	double amount;
	std::cout << "Enter the amount to deposit: $";
	std::cin >> amount;
	account.balance += amount;
	std::cout << "Deposited $" << amount << " into account " << account.accountNumber << std::endl;
}

void withdraw(BankAccount& account) {
	double amount;
	std::cout << "Enter the amount to withdraw: $";
	std::cin >> amount;
	if (account.balance >= amount) {
		account.balance -= amount;
		std::cout << "Withdrawn $" << amount << " from account " << account.accountNumber << std::endl;
	}
	else {
		std::cout << "Insufficient balance.\n";
	}
}

#pragma region Technical Part

void loadAccounts() {
	std::ifstream file("data/accounts.txt");
	if (!file) {
		std::cout << "Could not open accounts file.\n";
		return;
	}

	BankAccount account;
	while (file >> account.accountNumber >> account.accountHolder >> account.balance >> account.accountPassword) {
		accounts.push_back(account);
	}
	file.close();
}

void saveAccounts() {
    std::ofstream file("data/accounts.txt");
    if (!file) {
        std::cout << "Could not open accounts file for saving.\n";
        return;
    }

    file << std::fixed << std::setprecision(2); // Set precision to 2 decimal places

    for (const BankAccount& account : accounts) {
        file << account.accountNumber << " " << account.accountHolder << " " << account.balance << " " << account.accountPassword << std::endl;
    }

    file.close();
}

#pragma endregion