#include <stdio.h>
#include <string.h>
#include "file.h"

// Function to save contacts to CSV file
void saveContactsToFile(AddressBook *addressBook) 
{
  FILE* write = fopen("contactlist.csv","w");
  if ( write == NULL )
  {
    printf("Failed to 'w' open file\n");
    return;
  }
  
  int i = 0;
  while ( i < addressBook->contactCount )
  {
    // this logic stores details in an "name,email,number\n" format
    fprintf(write,"%s,%s,%s\n",
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].email,
                               addressBook->contacts[i].phone);
    i+=1;
  }
  fclose(write);
  return;
}

// Function to load contacts from CSV file
void loadContactsFromFile(AddressBook *addressBook) {
  FILE* read = fopen("contactlist.csv","r");
  if ( read == NULL )
  {
    printf("Failed to open 'r' file \n");
    return;
  }
  
  char line[50]; // an line string for fetching each details
  addressBook->contactCount = 0; // initializing count by zero
  
  while ( fgets(line,sizeof(line),read)) //fgets read each line by line till it EOF
  {
    char* name = strtok(line,","); // reads the first string before ','
    char* email = strtok(NULL,","); // reads the second string before ','
    char* phone = strtok(NULL, "\n"); // reads the last string before '\n'
    
    if ( name != NULL && email != NULL && phone != NULL ) // Check if all fields are parsed
    {
      strcpy(addressBook->contacts[addressBook->contactCount].name,name);
      strcpy(addressBook->contacts[addressBook->contactCount].email,email);
      strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
      (addressBook->contactCount)+=1; // increase count after every loading
    }
    
    // for preventing out of bounds 
    if ( addressBook->contactCount >= 100 )
    {
      printf("Contact count has been exceeded \n");
      break;
    }
  }
  fclose(read);
}
