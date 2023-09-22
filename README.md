# Banking System

The **Banking System** is a C++ program that simulates a simple banking system. 
It allows users to create accounts, log in, check account information, deposit, and withdraw money. 
Additionally, it provides administrative functions to list all accounts, delete accounts, and change account balances.

## Features

- User-friendly command-line interface.
- Secure password handling and validation.
- Account creation and login functionality.
- Account balance management (deposit and withdraw).
- Administrative capabilities to manage accounts.

## Getting Started

These instructions will help you set up and run the Banking System on your local machine.

### Prerequisites

- C++ compiler
- Git (optional, for cloning the repository)

### Installation

1. Clone the repository to your local machine (or download the ZIP file).

   ```shell
   git clone https://github.com/endynator/banking-system.git
   ```

2. Navigate to the project directory.

   ```shell
   cd banking-system
   ```

3. Compile the source code.

   ```shell
   g++ -o main main.cpp utils.cpp admin.cpp
   ```

### Usage

1. Run the program.

   ```shell
   ./main
   ```

2. Follow the on-screen instructions to create an account, log in, and perform banking operations.

### Administrative Functions

- To access administrative functions, log in with the admin account:

  - Account Number: 0
  - Password: admin

- Administrative options include:
  - Display all accounts
  - Delete an account
  - Change an account's balance

## Contributing

Contributions are welcome! Please follow these guidelines:

1. Fork the repository.
2. Create a branch: `git checkout -b feature/new-feature`.
3. Make your changes and commit them: `git commit -m 'Add new feature'`.
4. Push to your forked repository: `git push origin feature/new-feature`.
5. Create a pull request.

## Acknowledgments

- [OpenAI](https://www.openai.com) for providing the assistance to create this README.
  
