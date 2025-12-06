# Address Book
A command-line contact management system with persistent CSV storage and input validation.

## Description
This address book application lets you manage contacts with automatic validation and file-based storage. It supports creating, searching, editing, and deleting contacts with sorting capabilities.

## Features
- Create, search, edit, and delete contacts
- Sort contacts by name, number, or email
- Input validation for names, phone numbers, and emails
- CSV-based persistent storage
- Automatic data loading on startup

## Installation
Clone the repository:
```bash
git clone https://github.com/ArjunVasavan/address-book.git
cd address-book
```

## Compilation
```bash
gcc *.c -o addressbook
```

## Usage
### Running the Program
```bash
./addressbook
```

### Menu Options
```bash
1. Create contact    # Add new contact
2. Search contact    # Find by name, number, or email
3. Edit contact      # Modify existing contact
4. Delete contact    # Remove contact
5. List all contacts # Display with sorting options
6. Save contacts     # Save and exit
7. Exit              # Exit without saving
```

### Validation Rules
- **Name**: Alphabets only, one space required (first and last name)
- **Phone**: 10 digits, must be unique
- **Email**: Must contain '@' and '.', must be unique

## How It Works
The program stores contacts in `contactlist.csv` and automatically loads them on startup. It validates all inputs and uses bubble sort for organizing contacts by name, number, or email.

## Author
Arjun Vasavan

## License
This project is licensed under the [MIT License](./LICENSE).

> © 2025 Arjun Vasavan
