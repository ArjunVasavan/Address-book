#include <stdio.h>
#include <stdlib.h> //< > for representing library
#include <string.h>
#include <strings.h>
#include "contact.h" // whichever code on same directory is included
#include "file.h"

// Function prototypes for validation functions
int validate_email(char* , AddressBook* );
int validate_name(char*);
int validate_number(char*,AddressBook*);

// Function to list contacts with sorting options
void listContacts(AddressBook *addressBook, int sortCriteria)
{
  // Sort contacts based on the chosen criteria

  switch ( sortCriteria ) //sorting based on name 
  {
    case 1: // Sort by name using bubble sort
      {
        for ( int i = 0 ; i < (addressBook->contactCount - 1) ; i++) // Outer loop for passes
        {
          for ( int j = 0 ; j < (addressBook->contactCount - i - 1 ); j++ ) // Inner loop for comparisons
          {
            if (( strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name) > 0 )) // Compare names case-insensitively
            {
              Contact temp = addressBook->contacts[j]; // Temporary variable for swapping 
              addressBook->contacts[j] = addressBook->contacts[j+1]; // Swap contacts
              addressBook->contacts[j+1] = temp;
            }
          }
        }

        printf("==============================================================================================\n");
        printf("| %-28s | %-28s | %-28s |\n", "Name", "Number", "Email"); // Print table header
        printf("==============================================================================================\n");
        for ( int i = 0 ; i < addressBook->contactCount ; i++ ) // Loop through all contacts
        {
          printf("| %-28s | %-28s | %-28s |\n", // Print each contact with formatting
                 addressBook->contacts[i].name,
                 addressBook->contacts[i].phone,
                 addressBook->contacts[i].email);
        }
        printf("==============================================================================================\n");
        break;
      }

    case 2: //sorting based on number
      {
        for ( int i = 0 ; i < addressBook->contactCount - 1 ; i++) // Outer loop for bubble sort
        {
          for ( int j = 0 ; j < addressBook->contactCount - i - 1 ; j++ ) // Inner loop for comparisons
          {
            if (( strcasecmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone) > 0 )) // Compare phone numbers
            {
              Contact temp = addressBook->contacts[j]; // Temporary storage for swapping
              addressBook->contacts[j] = addressBook->contacts[j+1]; // Perform swap
              addressBook->contacts[j+1] = temp;
            }
          }
        }

        printf("==============================================================================================\n");
        printf("| %-28s | %-28s | %-28s |\n", "Name", "Number", "Email"); // Display header
        printf("==============================================================================================\n");
        for ( int i = 0 ; i < addressBook->contactCount ; i++ ) // Display all contacts
        {
          printf("| %-28s | %-28s | %-28s |\n",
                 addressBook->contacts[i].name,
                 addressBook->contacts[i].phone,
                 addressBook->contacts[i].email);
        }
        printf("==============================================================================================\n");
        break;
      }

    case 3: //sorting based on email
      {
        for ( int i = 0 ; i < addressBook->contactCount - 1 ; i++) // Bubble sort outer loop
        {
          for ( int j = 0 ; j < addressBook->contactCount - i - 1 ; j++ ) // Bubble sort inner loop
          {
            if (( strcasecmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email) > 0 )) // Compare email addresses
            {
              Contact temp = addressBook->contacts[j]; // Store contact temporarily
              addressBook->contacts[j] = addressBook->contacts[j+1]; // Swap positions
              addressBook->contacts[j+1] = temp;
            }
          }
        }

        printf("==============================================================================================\n");
        printf("| %-28s | %-28s | %-28s |\n", "Name", "Number", "Email"); // Print column headers
        printf("==============================================================================================\n");
        for ( int i = 0 ; i < addressBook->contactCount ; i++ ) // Print all sorted contacts
        {
          printf("| %-28s | %-28s | %-28s |\n",
                 addressBook->contacts[i].name,
                 addressBook->contacts[i].phone,
                 addressBook->contacts[i].email);
        }
        printf("==============================================================================================\n");
        break;
      }

    case 4: //normal listing
      {
        printf("==============================================================================================\n");
        printf("| %-28s | %-28s | %-28s |\n", "Name", "Number", "Email"); // Display table header
        printf("==============================================================================================\n");
        for ( int i = 0 ; i < addressBook->contactCount ; i++ ) // Loop through contacts without sorting
        {
          printf("| %-28s | %-28s | %-28s |\n", // Print contact info
                 addressBook->contacts[i].name,
                 addressBook->contacts[i].phone,
                 addressBook->contacts[i].email);
        }
        printf("==============================================================================================\n");
        break;
      }
  }
}

// Initialize the address book
void initialize(AddressBook *addressBook) 
{
  addressBook->contactCount = 0; // Set initial contact count to zero

  // Load contacts from file during initialization (After files)
  loadContactsFromFile(addressBook); 
}

// Save contacts and exit the program
void saveAndExit(AddressBook *addressBook) 
{
  saveContactsToFile(addressBook); // Save contacts to file
  exit(EXIT_SUCCESS); // Exit the program
}

// Function to create a new contact
void createContact(AddressBook *addressBook)
{
  char name[50],number[50],email[50]; // Local variables to store input

  /* Define the logic to create a Contacts */
  printf("Enter the details\n\n");
  printf("1.Enter the name and surname :");

  scanf(" %[^\n]",name); // Read name including spaces

  if( validate_name(name) == 0 ) // Validate the entered name
  {
    printf("=== Error! Enter an Valid Name ===!");
    return; // Exit function if name is invalid
  }

  printf("2.Enter the number :");

  scanf(" %[^\n]",number); // Read phone number

  if ( validate_number(number,addressBook) == 0 ) // Validate phone number
  {
    printf("=== Error! Enter an Valid Number ===\n");
    return; // Exit if number is invalid
  }

  printf("3.Enter the email :");
  scanf("%s",email); // Read email address
  
  if ( validate_email(email,addressBook) == 0) // Validate email format and uniqueness
  {
    printf("=== Error! Enter an valid email ===\n");
    return; // Exit if email is invalid
  }

  printf("\n=== <> Contact details have been added Successfully <> === \n");

  // conversion - Copy validated data to address book
  strcpy(addressBook->contacts[addressBook->contactCount].name,name); // Copy name
  strcpy(addressBook->contacts[addressBook->contactCount].phone,number); // Copy phone
  strcpy(addressBook->contacts[addressBook->contactCount].email,email); // Copy email

  addressBook->contactCount+=1; // Increment total contact count
}

// Function to search for a contact
int searchContact(AddressBook *addressBook) 
{
  char finder[50]; //its an string for storing what to search
  int option; // Variable to store search option

  printf("===<> Enter Searching Options <>===\n\n");
  printf("1.Search By Name\n");
  printf("2.Search By Number\n");
  printf("3.Search By Email\n");
  printf("Choose an Option :");

  scanf("%d",&option); // Read user's choice

  int flag = 0; // this flag is created for returning 1 when successfully searched
 
  switch (option) 
  {
    case 1: // Search by name
      {
        printf("Enter the name to search :");

        getchar(); // Clear input buffer
        scanf("%[^\n]",finder); // Read name to search

        for ( int i = 0 ; i < addressBook->contactCount ; i++ ) // Loop through all contacts
        {
          if ( strcasecmp(finder, addressBook->contacts[i].name) == 0 ) // Compare names case-insensitively
          {
            printf("================================================================================================================\n");
            printf("| %-10s | %-28s | %-28s | %-28s |\n", "ID", "Name", "Number", "Email"); // Print header with ID
            printf("================================================================================================================\n");
            printf("| %-10d | %-28s | %-28s | %-28s |\n" // Print found contact with index
                   ,i,addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            printf("================================================================================================================\n");
            flag = 1; // Set flag to indicate successful search
          }
        }
        break;
      }
    case 2: // Search by phone number
      {
        printf("Enter the number to search :");

        getchar(); // Clear input buffer
        scanf("%[^\n]",finder); // Read phone number to search

        for ( int i = 0 ; i < addressBook->contactCount ; i++ ) // Iterate through contacts
        {
          if ( strcasecmp(finder, addressBook->contacts[i].phone) == 0 ) // Compare phone numbers
          {
            printf("================================================================================================================\n");
            printf("| %-10s | %-28s | %-28s | %-28s |\n", "ID", "Name", "Number", "Email"); // Display header
            printf("================================================================================================================\n");
            printf("| %-10d | %-28s | %-28s | %-28s |\n", // Display found contact
                   i,addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            printf("================================================================================================================\n");

            flag = 1; // Mark as found
          }
        }
        break;
      }
    case 3: // Search by email
      {
        printf("Enter the email to search :");

        getchar(); // Clear input buffer
        scanf("%[^\n]",finder); // Read email to search

        for ( int i = 0 ; i < addressBook->contactCount ; i++ ) // Search through all contacts
        {
          if ( strcasecmp(finder, addressBook->contacts[i].email) == 0 ) // Compare email addresses
          {
            printf("================================================================================================================\n");
            printf("| %-10s | %-28s | %-28s | %-28s |\n", "ID", "Name", "Number", "Email"); // Print table header
            printf("================================================================================================================\n");
            printf("| %-10d | %-28s | %-28s | %-28s |\n", // Print matching contact
                   i,addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            printf("================================================================================================================\n");

            flag = 1; // Set success flag
          }
        }
        break;
      }
  }
  
  if ( flag == 1 ) // Check if contact was found
  {
    return 1; // Return success
  }
  else
  {
    return 0; // Return failure
  }
}

// Function to edit an existing contact
void editContact(AddressBook *addressBook)
{
  if(searchContact(addressBook) == 1 ) // First search for the contact to edit
  {
    int index; // for iterating contacts

    printf("Enter the index you want to edit : ");

    scanf("%d",&index); // Read the index of contact to edit

    // for checking if index if in bound
    if (index < 0 || index >= addressBook->contactCount) {
      printf("=== Error! Invalid index ===\n");
      return;
    }

    int option; // Variable to store edit option

    printf("<>===<> EDIT MENU <>===<>\n\n");
    printf("1.edit the name\n");
    printf("2.edit the number\n");
    printf("3.edit the email\n");
    printf("Choose any one option ? : ");

    scanf("%d",&option); // Read user's choice for what to edit

    char new[50]; // new is an string for storing what should be edited

    switch (option) 
    {
      case 1 : // Edit name
        {
          printf("Enter the new name : ");

          getchar(); // Clear input buffer
          scanf("%[^\n]",new); // Read new name

          if( validate_name(new) == 0 ) // Validate the new name
          {
            printf("=== Error! Enter an Valid Name ===\n");
            return; // Exit function if name is invalid
          }

          strcpy(addressBook->contacts[index].name,new); // Copy new name to contact
          break;
        }
      case 2 : // Edit phone number
        {
          printf("Enter the new number : ");

          getchar(); // Clear input buffer
          scanf("%[^\n]",new); // Read new phone number

          if ( validate_number(new,addressBook) == 0 ) // Validate phone number
          {
            printf("=== Error! Enter an Valid Number ===\n");
            return; // Exit if number is invalid
          }

          strcpy(addressBook->contacts[index].phone,new); // Update phone number
          break;
        }
      case 3 : // Edit email
        {
          printf("Enter the new email : ");

          getchar(); // Clear input buffer
          scanf("%[^\n]",new); // Read new email

          if ( validate_email(new,addressBook) == 0) // Validate email format and uniqueness
          {
            printf("=== Error! Enter an valid email ===\n");
            return; // Exit if email is invalid
          }

          strcpy(addressBook->contacts[index].email,new); // Update email address
          break;
        }

    }
    printf("<>===<>Data has been Updated!<>===<>\n\n"); // Success message
  }
  else 
  {
    printf("<>===<>Data Not Found<>===<>\n"); // Message when contact not found
  }
}

// Function to delete a contact
void deleteContact(AddressBook *addressBook)
{

  if ( searchContact(addressBook)) // First search for contact to delete
  {
    int index; // Variable to store index of contact to delete

    printf("Enter the index you want to delete :");
    scanf("%d",&index); // Read index from user

    // for checking if index is in bound
    if (index < 0 || index >= addressBook->contactCount) {
    printf("=== Error! Invalid index ===\n");
    return;
}
    for (int i = index ; i < (addressBook->contactCount)-1 ; i++ ) // Shift all contacts after deleted one
    {
      addressBook->contacts[i] = addressBook->contacts[i+1]; // Move contact one position left
    }

    (addressBook->contactCount)-=1; // Decrease total contact count
  }
  else
  {
    printf("<> === <> Data Not Found <> === <> \n"); // Message when contact not found
  }
}
