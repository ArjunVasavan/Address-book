#include <stdio.h>
#include "contact.h"

int main()
{
  int choice,sortChoice;

  AddressBook addressBook;

  initialize(&addressBook); // Initialize the address book

  do {

    printf("\n=== <> Address Book Menu <> ===\n");
    printf("1. Create contact\n");
    printf("2. Search contact\n");
    printf("3. Edit contact\n");
    printf("4. Delete contact\n");
    printf("5. List all contacts\n");
    printf("6. Save contacts\n");		
    printf("7. Exit\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    switch (choice)
    {
      case 1:
        createContact(&addressBook);
        break;
      case 2:
        if(!searchContact(&addressBook))
        {
          printf("=== <> Data Not found <> ===\n");
        }
        break;
      case 3:
        editContact(&addressBook);
        break;
      case 4:
        deleteContact(&addressBook);
        break;
      case 5:
        printf("\n=== <> List All Contact Menu <> ===\n\n");
        printf("1. List By Name\n");
        printf("2. List By Number\n");
        printf("3. List By Email\n");
        printf("4. Default List \n");
        printf("Enter Your Choise: ");

        scanf("%d",&sortChoice);

        listContacts(&addressBook, sortChoice);
        break;
      case 6:
        printf("Saving and Exiting...\n");
        saveContactsToFile(&addressBook); 
        return 0;
      case 7:
        {
          printf("You Have successfully exited\n");
          break;
        }
      default:
        printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 7);

  return 0;

}
