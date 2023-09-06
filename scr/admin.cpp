#include "account.h"
#include <iostream>

void AdminListAllAccounts() {
	std::cout << "List of all accounts:\n";
	for (const BankAccount& account : accounts) {
		std::cout << "Account Number: " << account.accountNumber << ", Holder: " << account.accountHolder << ", Balance: $" << account.balance << std::endl;
	}
}

void AdminDelAccount() {
	int a_num;
	std::cout << "\nAccount number: "; std::cin >> a_num;

	if (a_num == 0) return;

	for (auto it = accounts.begin(); it != accounts.end(); ++it) {
		if (it->accountNumber == a_num) {
			accounts.erase(it);
		}
	}
}

void AdminChangeBalance() {
	int a_num, val;
	std::cout << "\nAccount number: "; std::cin >> a_num;

	std::cout << "New value: "; std::cin >> val;

	for (BankAccount& account : accounts) {
		if (account.accountNumber == a_num) {
			account.balance = val;
		}
	}
}
