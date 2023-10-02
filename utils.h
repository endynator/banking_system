#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "account.h"

using namespace std;

int generateAccountNumber();
void displayMenu();
void displayAdminMenu();
bool isStrongPassword(string password);

#endif