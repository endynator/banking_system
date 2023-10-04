#include "../headers/account.h"
#include "../headers/utils.h"
#include "../headers/main.h"
#include "../headers/admin.h"
#include "../headers/logging.h"
#include "../headers/actions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cstdlib>

std::vector<BankAccount> accounts;

std::vector<Log> Logs;

void displayAccountInfo(const BankAccount& account) {
	std::string pw;
	std::cout << "Password: ";
	std::cin.ignore();
	std::getline(std::cin, pw);

	if (account.accountPassword == pw) {
		std::cout << "Account Number: " << account.accountNumber << std::endl;
		std::cout << "Account Holder: " << account.accountHolder << std::endl;
		std::cout << "Balance: $" << account.balance << std::endl;
		return;
	}

	std::cout << red << "Incorrect password.\n" << upd;
}

void loadAccounts() {
	accounts.clear(); // Clear the existing data

	std::filesystem::path dataDirectory("Accounts");
	if (!std::filesystem::exists(dataDirectory)) {
		std::cout << red << "Accounts directory not found.\n" << upd;
		return;
	}

	for (const auto& entry : std::filesystem::directory_iterator(dataDirectory)) {
		if (entry.is_regular_file()) {
			std::ifstream file(entry.path().string());
			if (!file) {
				std::cout << red << "Could not open account file for loading: " << entry.path().string() << upd << std::endl;
				continue; // Skip to the next account if the file cannot be opened
			}

			BankAccount account;
			if (file >> account.accountNumber >> account.accountHolder >> account.balance >> account.accountPassword) {
				accounts.push_back(account);
			}
			else {
				std::cout << red << "Error reading account data from file: " << entry.path().string() << upd << std::endl;
			}
			file.close();
		}
	}
}

void saveAccounts() {
	for (const BankAccount& account : accounts) {
		std::ofstream file("Accounts/" + std::to_string(account.accountNumber) + ".txt");
		if (!file) {
			std::cout << red << "Could not open account file for saving: " << account.accountNumber << ".txt\n" << upd;
			continue; // Skip to the next account if file cannot be opened
		}

		file << std::fixed << std::setprecision(2);
		file << account.accountNumber << "\n" << account.accountHolder << "\n" << account.balance << "\n" << account.accountPassword << std::endl;
		file.close();
	}
}

void init(BankAccount& account) { 
	int choice;
	if (account.accountNumber == 0) {
		do {
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
				saveAccounts();
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
			performTransaction(account);
			break;
		case 5:
			displayLogs(account);
			break;
		case 6:
			saveAccounts();
			system("cls");
			std::cout << green << "Logged out successfuly.\n" << upd;
			loop();
			break;
		case 7:
			saveAccounts();
			std::cout << "Exiting the program.\n";
			return;
		default:
			std::cout << red << "Invalid choice. Please try again.\n" << upd;
		}
	} while (choice != 6 && choice != 7);
}
