#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "account.h"

using namespace std; //??????????????

/*
I've been trying to solve an error that said "string is undeclared identifier".
I did everything. Check entire solution couple times, went on stackOverflow.
Some dude told that I shouldn't use 'using namespace std;' at all and I did.
Didn't solve the problem tho. 
Researching again I tryied putting '#include <string>' into every fricking file.
Didn't solve the problem tho.

One dude said this: 
"To use the standard string class in C++ you need to #include <string>. 
Once you've added the #include directive 
string will be defined in the std namespace and you can refer to it as std::string".

I thought about it for a second. And I decided to put using namespace std; in it.
Who would've known it was the solution. 
To this day, I struggle to understand why does this header requires this kind of structure.
*/

int generateAccountNumber();
void displayMenu();
void displayAdminMenu();
bool isStrongPassword(string password);

#endif