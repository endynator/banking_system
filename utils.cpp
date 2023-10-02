#include "utils.h"
#include "account.h"
#include <cctype>
#include <iostream>
#include <string>

int generateAccountNumber() {
	static int accountNumber = 1000; // Starting account number
	return ++accountNumber;
}

bool isStrongPassword(std::string password) {
	// Check the length of the password
	if (password.length() < 8) {
		std::cout << "Password is too short. It should be at least 8 characters long.\n";
		return false;
	}

	bool hasUpperCase = false;
	bool hasLowerCase = false;
	bool hasDigit = false;
	bool hasSpecialChar = false;

	// Check each character in the password
	for (char c : password) {
		if (isupper(c))
			hasUpperCase = true;
		else if (islower(c))
			hasLowerCase = true;
		else if (isdigit(c))
			hasDigit = true;
		else if (ispunct(c))
			hasSpecialChar = true;
	}

	// Check character type requirements
	if (!hasUpperCase) {
		std::cout << "Password must contain at least one uppercase letter.\n";
	}
	if (!hasLowerCase) {
		std::cout << "Password must contain at least one lowercase letter.\n";
	}
	if (!hasDigit) {
		std::cout << "Password must contain at least one digit.\n";
	}
	if (!hasSpecialChar) {
		std::cout << "Password must contain at least one special character.\n";
	}

	// Check if all requirements are met
	return hasUpperCase && hasLowerCase && hasDigit && hasSpecialChar;
}

void displayAdminMenu() {
	std::cout << "\nBank's Admin Menu\n";
	std::cout << "1. Display All Accounts\n";
	std::cout << "2. Delete an account\n";
	std::cout << "3. Change Account's balance\n";
	std::cout << "4. Exit\n";
	std::cout << "Enter your choice: ";
}

void displayMenu() {

	std::cout << "\nBanking System Menu\n";
	std::cout << "1. Display Account Info\n";
	std::cout << "2. Deposit\n";
	std::cout << "3. Withdraw\n";
	std::cout << "4. Remit\n";
	std::cout << "5. History\n";
	std::cout << "6. Exit\n";
	std::cout << "7. Log Out\n";
	std::cout << "Enter your choice: ";

}
