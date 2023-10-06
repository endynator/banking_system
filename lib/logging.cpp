#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include "../headers/account.h"

void saveLogs() {
	std::filesystem::create_directory("logs");

	for (const BankAccount& account : accounts) {
		std::ofstream file("logs/" + std::to_string(account.accountNumber) + ".txt", std::ios::app);
		if (!file) {
			std::cerr << red << "Could not open log file for account " << account.accountNumber << ".txt\n" << upd;
			continue;
		}

		for (auto& log : Logs) {
			if (log.accountNumber == account.accountNumber) {

				file << log.dateTime << " | " << log.action << " | " << log.balance << " -> " << log.afterBalance;

				if (log.action == "OutTransaction") file << " | sent to: " << log.recipientAccountNumber;
				if (log.action == "InTransaction") file << " | recieved from: " << log.recipientAccountNumber;

				for (int i = 0; i < Logs.size(); i++) {
					if (Logs[i].accountNumber == log.accountNumber) Logs.erase(Logs.begin() + i);
				}
				file << std::endl;
			}
		}
		file.close();
	}
}

void displayLogs(const BankAccount& account) {
	std::ifstream file("logs/" + std::to_string(account.accountNumber) + ".txt");
	if (!file) {
		std::cout << red << "No transaction logs found for account " << account.accountNumber << std::endl << upd;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
	}

	file.close();
}
