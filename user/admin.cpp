#include "../headers/account.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>

void AdminListAllAccounts() {
	std::cout << "List of all accounts:\n";
	for (const BankAccount& account : accounts) {
		std::cout << "Account Number: " << account.accountNumber << ", Holder: " << account.accountHolder << ", Balance: $" << account.balance << std::endl;
	}
}

void deleteAccountFiles(const std::vector<BankAccount>& accounts, std::filesystem::path dataDirectory) { //removes a needless .txt files 
	// Get a list of all files in the "Accounts" directory
	for (const auto& entry : std::filesystem::directory_iterator(dataDirectory)) {
		if (entry.is_regular_file()) { 
			// Extract the account number from the file name
			std::string fileName = entry.path().filename().string();
			int accountNumber = std::stoi(fileName);

			// Check if the account number exists in the vector
			bool accountExists = std::any_of(accounts.begin(), accounts.end(),
				[accountNumber](const BankAccount& acc) {
					return acc.accountNumber == accountNumber;
				});

			// If the account doesn't exist in the vector, delete the file
			if (!accountExists) {
				std::filesystem::remove(entry.path());
				std::cout << green << "Deleted account file: " << entry.path().string() << upd << std::endl;
			}
		}
	}
}

void AdminDelAccount() {
	int a_num;
	std::cout << "\nAccount number: "; std::cin >> a_num;

	// Use std::find_if with a lambda function to search by account number
	auto it = std::find_if(accounts.begin(), accounts.end(), [a_num](const BankAccount& account) {
		return account.accountNumber == a_num;
		});

	std::filesystem::path dataDirectory("Accounts");
	std::filesystem::path logsDirectory("logs");

	if (it != accounts.end()) {
		// Erase the account if found
		accounts.erase(it);
		// Call 'deleteAccountFiles' to clear up any logs or account info stored in .txt files
		deleteAccountFiles(accounts, dataDirectory);
		deleteAccountFiles(accounts, logsDirectory);
	}
	else {
		std::cout << red << "Account not found.\n" << upd;
	}
}

void AdminChangeBalance() {
	int a_num, val;
	std::cout << "\nAccount number: "; std::cin >> a_num;

	std::cout << "New value: "; std::cin >> val;

	for (BankAccount& account : accounts) if (account.accountNumber == a_num) account.balance = val;
}
