#include <stdio.h>
#include <stdlib.h> //< > for representing library
#include <string.h>
#include <strings.h>
#include <time.h>
#include "contact.h" // whichever code on same directory is included

// Function to validate name format
int validate_name( char* name )
{
  int i = 0;
  int character_condition = 1;
  
  while ( name[i] )
  {
    if (!( name[i] >= 'A' && name[i] <= 'Z' || name[i] >= 'a' && name[i] <= 'z' || name[i] == ' ')) // checks =>> if only alphabet and space is present
    {
      character_condition = 0;
    }
    i+=1;
  }
  
  int space_condition = 1;
  i = 0;
  int space_count = 0;
  
  while ( name[i] )
  {
    if ( name[0] == ' ' ) // for checking if space is beginning
    {
      space_condition = 0;
      break;
    }
    if ( name[i] == ' ' )
    {
      space_count+=1;
    }
    i+=1;
  }
  
  if ( space_count ==  1 ) // Validate exactly one space
  {
    space_condition = 1;
  }
  else 
  {
    space_condition = 0;
  }
  
  if ( character_condition == 1 )
  {
    if ( space_condition == 1 )
    {
      return 1;
    }
  }
  return 0; // Return 0 if validation fails
}

// Function to validate phone number format and uniqueness
int validate_number( char* number , AddressBook* addressBook )
{
  int i = 0;
  int unique = 1;
  int digitonly = 1;
  
  while ( i < addressBook->contactCount ) // Check for duplicate numbers
  {
    if ( strcmp(number,addressBook->contacts[i].phone) == 0 )
    {
      unique = 0;
    }
    i+=1;
  }
  
  i = 0;
  while ( number[i] ) // Check if all characters are digits
  {
    if (!( number[i] >= '0' && number[i] <= '9') )
    {
      digitonly = 0;
    }
    i+=1;
  }
  
  if ( strlen (number) == 10 ) // Validate 10-digit number
  {
    if ( digitonly == 1 )
    {
      if ( unique == 1 )
      {
        return 1;
      }
    }
  }
  return 0;
}

// Function to validate email format and uniqueness
int validate_email( char* email , AddressBook* addressBook )
{
  char* where_is_at = strchr(email,'@'); // Find @ symbol
  char* where_is_dot = strchr(email,'.'); // Find . symbol
  
  if ( where_is_at != NULL && where_is_dot != NULL && strchr(email,' ') == NULL && where_is_dot > where_is_at ) //checks =>> Dot and And , space .
  {
    if ( where_is_at != email && *(where_is_at + 1) != '\0'  ) // checks =>> if at is at beginning and if at is at end
    {
      if ( where_is_dot != email && *(where_is_dot + 1) != '\0'  ) // cheks =>> if dot is at beginning and if dot is at end
      {
        int i = 0;
        int flag = 1;
        
        while ( i < addressBook->contactCount) // Check for duplicate email
        {
          if ( strcmp(email,addressBook->contacts[i].email) == 0 ) // checks if theres already existing contact
          {
            flag = 0;
          }
          i+=1;
        }
        
        if  ( flag == 1 )
        {
          for ( int i = 0 ; email[i] ; i++ ) // Validate allowed email characters
          {
            if ( ! (email[i] >= 'a' && email[i] <= 'z' || email[i] >= '0' && email[i] <= '9' || email[i] =='.' || email[i] == '@'))
            {
              return 0;
            }
          }
          return 1;
        }
      }
    }
  }
  return 0;
}
