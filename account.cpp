#include "account.h"
#include "utils.h"
#include "main.h"
#include "admin.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <filesystem>

/*
struct tm {
	int tm_sec;    //Seconds: 0-61
	int tm_min;    //Minutes: 0-59
	int tm_hour;   //Hours:   0-23
	int tm_mday;   //Day of month: 1-31
	int tm_mon;    //Month: 0-11
	int tm_year;   //Years since 1900
	int tm_wday;   //Days since Sunday: 0-6
	int tm_yday;   //Days since January 1: 0-365
	int tm_isdst;  //Daylight Savings Time
}
*/

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

	std::cout << "Incorrect password.\n";
}

#pragma region Logs Manipulations

void saveLogs() {
	std::filesystem::create_directory("logs");

	for (const BankAccount& account : accounts) {
		std::ofstream file("logs/" + std::to_string(account.accountNumber) + ".txt", std::ios::app);
		if (!file) {
			std::cerr << "Could not open log file for account " << account.accountNumber << ".txt\n";
			continue;
		}

		for (auto& log : Logs) {
			if (log.accountNumber == account.accountNumber) {

				file << log.dateTime << " | " << log.action << " | " << log.balance << " -> " << log.afterBalance;

				if (log.action == "OutTransaction" || log.action == "InTransaction") file << " | sent to: " << log.recipientAccountNumber;

				cout << endl;

				for (int i = 0; i < Logs.size(); i++) {
					if (Logs[i].accountNumber == log.accountNumber) Logs.erase(Logs.begin() + i);
				}
			}

			if (log.action == "Transaction") {
				file << " | Recipient: " << log.recipientAccountNumber;
			}
			file << std::endl;
		}
		file.close();
	}
}

// Function to display transaction logs for an account
void displayLogs(const BankAccount& account) {
	std::ifstream file("logs/" + std::to_string(account.accountNumber) + ".txt");
	if (!file) {
		std::cout << "No transaction logs found for account " << account.accountNumber << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
	}

	file.close();
}

#pragma endregion

#pragma region Balance Manipulations

void performTransaction(BankAccount& sender) {
	double amount;
	int n = -1;
	do {
		cout << "The receiver's account number (0 to cancel): "; cin >> n;
	} while (n < 1001 && n > accounts[1].accountNumber - accounts.size() - 1 || n == sender.accountNumber);

	cout << "Amount to send: "; cin >> amount;

	for (auto& recipient : accounts) {
		if (recipient.accountNumber == n) {

			if (sender.balance >= amount) {

				// Log the transaction
				Log senderLog;
				Log recipientLog;

				senderLog.accountNumber = sender.accountNumber;
				recipientLog.accountNumber = recipient.accountNumber;

				time_t now = time(0);
				tm* localTime = localtime(&now);
				char buffer[20];
				strftime(buffer, sizeof(buffer), "%d.%m.%Y | %H:%M", localTime);

				senderLog.dateTime = buffer;
				recipientLog.dateTime = buffer;

				senderLog.balance = sender.balance;
				recipientLog.balance = recipient.balance;

				sender.balance -= amount;
				recipient.balance += amount;

				senderLog.afterBalance = sender.balance; // Set the correct afterBalance
				recipientLog.afterBalance = recipient.balance; // Set the correct afterBalance

				senderLog.recipientAccountNumber = recipient.accountNumber;
				recipientLog.recipientAccountNumber = sender.accountNumber;

				// Determine the action
				senderLog.action = "OutTransaction";
				recipientLog.action = "InTransaction";

				// Save logs
				Logs.push_back(senderLog);
				Logs.push_back(recipientLog);

				// Save the updated accounts and transaction logs
				saveAccounts();
				saveLogs();
			}
			else {
				std::cout << "Insufficient balance for the transaction.\n";
			}
		}
	}
}

void deposit(BankAccount& account) {
	double amount;
	std::cout << "Enter the amount to deposit: $";
	std::cin >> amount;

	// Log the deposit
	Log log;
	time_t now = time(0);
	tm* localTime = localtime(&now);
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%d.%m.%Y | %H:%M", localTime);

	log.balance = account.balance;
	account.balance += amount;
	std::cout << "Deposited $" << amount << " into account " << account.accountNumber;

	log.accountNumber = account.accountNumber;
	log.dateTime = buffer;
	log.action = "Deposit";
	log.afterBalance = account.balance; // Set the correct afterBalance

	Logs.push_back(log);

	// Save the updated accounts and transaction logs
	saveAccounts();
	saveLogs();
}

void withdraw(BankAccount& account) {
	double amount;
	std::cout << "Enter the amount to withdraw: $";
	std::cin >> amount;
	if (account.balance >= amount) {
		// Log the withdrawal
		Log log;
		time_t now = time(0);
		tm* localTime = localtime(&now);
		char buffer[20];
		strftime(buffer, sizeof(buffer), "%d.%m.%Y | %H:%M", localTime);

		log.balance = account.balance;
		account.balance -= amount;
		std::cout << "Withdrawn $" << amount << " from account " << account.accountNumber;

		log.accountNumber = account.accountNumber;
		log.dateTime = buffer;
		log.action = "Withdrawal";
		log.afterBalance = account.balance; // Set the correct afterBalance

		Logs.push_back(log);

		// Save the updated accounts and transaction logs
		saveAccounts();
		saveLogs();
	}
	else {
		std::cout << "Insufficient balance.\n";
	}
}

#pragma endregion

#pragma region Save/Load

void loadAccounts() {
	accounts.clear(); // Clear the existing data

	std::filesystem::path dataDirectory("data");
	for (const auto& entry : std::filesystem::directory_iterator(dataDirectory)) {
		if (entry.is_regular_file()) {
			std::ifstream file(entry.path().string());
			if (!file) {
				std::cout << "Could not open account file for loading: " << entry.path().string() << std::endl;
				continue; // Skip to the next account if the file cannot be opened
			}

			BankAccount account;
			if (file >> account.accountNumber >> account.accountHolder >> account.balance >> account.accountPassword) {
				accounts.push_back(account);
			}
			else {
				std::cout << "Error reading account data from file: " << entry.path().string() << std::endl;
			}
			file.close();
		}
	}
}

void saveAccounts() {
	for (const BankAccount& account : accounts) {
		std::ofstream file("data/" + std::to_string(account.accountNumber) + ".txt");
		if (!file) {
			std::cout << "Could not open account file for saving: " << account.accountNumber << ".txt\n";
			continue; // Skip to the next account if file cannot be opened
		}

		file << std::fixed << std::setprecision(2);
		file << account.accountNumber << "\n" << account.accountHolder << "\n" << account.balance << "\n" << account.accountPassword << std::endl;
		file.close();
	}
}

#pragma endregion

void init(BankAccount& account) { //Function that asks and recieves answer
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
			std::cout << "Exiting the program.\n";
			return;
		case 7:
			std::cout << "Logged out successfuly.\n";
			saveAccounts();
			loop();
			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 4 && choice != 5);
}
