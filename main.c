#include <stdio.h>
#include "FUNC.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Include this for the toupper function

void main(void)
{
    int check = 0;
    int choice1 = 0;
    User s1[100];  // Assuming you meant to declare an array of User
    // While loop for login
    while (1)
    {
        check = login(s1);
		int accnum = count_accounts("accounts.txt");
		accounts *accounts_infile = load(accnum);
        if (check == 1)
        {
            printf("Welcome back\n");
            printf("\nWhat do you want to do?\nL Load account data.\nS Search.\nE Exit system.\n");

            fflush(stdin);
            scanf(" %c", &choice1);
            choice1 = toupper(choice1);

            // Switch case for the choices of the admin
            switch (choice1)
            {
                case 'L':
                    printf("Test is valid\n");
                    // Now you can write the code here
                    break;
                case 'S':
                    // EXTRA EXAMPLE
                    break;
                case 'E':
                    // Add code for exiting the system
                    break;
                default:
                    printf("Invalid choice\n");
            }
        }
        else
        {
            printf("Exiting system\n");
            break;
        }
    }
}
