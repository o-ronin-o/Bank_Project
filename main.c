#include <stdio.h>
#include "FUNC.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int check = 0;
    int choice1 = 0;
    User s1[100];  // Assuming you meant to declare an array of User

    // While loop for login
    while (1)
    {
        check = login(s1);

        int number_of_accounts = count_accounts();
        accounts *accounts_infile = load(number_of_accounts);

        if (check == 1)
        {
            printf("Welcome back\n");
            printf("\nMenu:\n");
            printf("1. ADD\n");
            printf("2. DELETE\n");
            printf("3. MODIFY\n");
            printf("4. SEARCH\n");
            printf("5. ADVANCED SEARCH\n");
            printf("6. WITHDRAW\n");
            printf("7. DEPOSIT\n");
            printf("8. TRANSFER\n");
            printf("9. REPORT\n");
            printf("10. PRINT\n");
            printf("11. QUIT\n");

            fflush(stdin);
            scanf("%d", &choice1);

            // Switch case for the choices of the admin
            switch (choice1)
            {
                case 1:
                    // Call the add function here
                    break;
                case 2:
                    delete_account(accounts_infile, &number_of_accounts);
                    break;
                case 3:
                    modify(accounts_infile, number_of_accounts);
                    break;
                case 4:
                    // Call the search function here
                    break;
                case 5:
                    advanced_search(accounts_infile, number_of_accounts);
                    break;
                case 6:
                    withdraw(accounts_infile, number_of_accounts);
                    break;
                case 7:
                    deposit(accounts_infile, number_of_accounts);
                    break;
                case 8:
                    trans(accounts_infile, number_of_accounts);
                    break;
                case 9:
                    report(accounts_infile, number_of_accounts);
                    break;
                case 10:
                    print_sorted(accounts_infile, number_of_accounts);
                    break;
                case 11:
                    // Add code for exiting the system
                    break;
                default:
                    printf("Invalid option\n");
                    break;
            }
        }
        else if (check == 0)
        {
            printf("Invalid username or password\n");
        }
        else
        {
            printf("Error: File not found.\n");
        }
    }

    return 0;
}
