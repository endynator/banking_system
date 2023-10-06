#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include "../headers/account.h"
#include "../headers/logging.h"

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
				tm* localTime = localtime(&now); // Getting time
				char buffer[20];
				strftime(buffer, sizeof(buffer), "%d.%m.%Y | %H:%M", localTime); // Converting time into readable string

				senderLog.dateTime = buffer;
				recipientLog.dateTime = buffer;

				senderLog.balance = sender.balance;
				recipientLog.balance = recipient.balance;

				sender.balance -= amount;
				recipient.balance += amount;

				senderLog.afterBalance = sender.balance;
				recipientLog.afterBalance = recipient.balance; 

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
				std::cout << red << "Insufficient balance for the transaction.\n" << upd;
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
	tm* localTime = localtime(&now); // Getting time
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%d.%m.%Y | %H:%M", localTime); // Converting time into readable string

	log.balance = account.balance;
	account.balance += amount;
	std::cout << "Deposited $" << amount << " into account " << account.accountNumber << std::endl;

	log.accountNumber = account.accountNumber;
	log.dateTime = buffer;
	log.action = "Deposit";
	log.afterBalance = account.balance; 

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
		tm* localTime = localtime(&now); // Getting time
		char buffer[20];
		strftime(buffer, sizeof(buffer), "%d.%m.%Y | %H:%M", localTime); // Converting time into readable string

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
		std::cout << red << "Insufficient balance.\n" << upd;
	}
}
