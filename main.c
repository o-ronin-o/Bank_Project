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
        char againChoice;

        int number_of_accounts = count_accounts();
        accounts *accounts_infile = load(number_of_accounts);

        if (check == 1)
        {
            printf("Welcome back\n");
            printf("\nMenu:\n\n");
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
                    do{
                    add(accounts_infile,&number_of_accounts);
                    printf("do you want to add again (Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    break;
                case 2:
                    do{
                    delete_account(accounts_infile, &number_of_accounts);
                    printf("do you want to delete again (Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    break;
                case 3:
                    do{
                    modify(accounts_infile, number_of_accounts);
                    printf("do you want to modify again (Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    break;
                case 4:
                    do{
                    searchAccount(accounts_infile, number_of_accounts);
                    printf("do you want to search again (Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    break;
                case 5:
                    do{
                    advanced_search(accounts_infile, number_of_accounts);
                    printf("do you want to do another advanced search again (Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    break;
                case 6:
                    do{
                    withdraw(accounts_infile, number_of_accounts);
                    printf("do you want to withdraw again (Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    break;
                  case 7:
                    do{
                    deposit(accounts_infile, number_of_accounts);
                    printf("do you want to deposit again (Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    break;
                case 8:
                    do{
                    trans(accounts_infile, number_of_accounts);
                    printf("do you want to do another transaction(Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    break;
                case 9:
                    do{
                    report(accounts_infile,number_of_accounts);
                    printf("do you want to print another report(Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    break;
                case 10:
                    do{
                    print_sorted(accounts_infile, number_of_accounts);
                    printf("do you want to print again(Y/N): \n");
                    scanf(" %c", &againChoice);
                    if (againChoice == 'y' || againChoice == 'Y')
                        continue;
                    else
                        break;
                    }while(1);
                    print_sorted(accounts_infile, number_of_accounts);
                    break;
                case 11:
                    printf("exiting the system...");
                    exit(1);
                default:
                    printf("Invalid option\n");
                    break;
            }
        }
        else if (check == 0)
        {
            printf("Invalid username or password\n");
            printf("Please try Again!\n\n");
        }
        else
        {
            printf("Error: File not found.\n");
        }
    }

    return 0;
}
