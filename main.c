/*
NAME: Omar.W.Al-Qattan 				   || 	        last update: December 21,2023
NAME: Abdallah.A.Na'eem 			   ||		last update: 
NAME: Abdelrahman.A.Abdo(7asal eh) 	           || 		last update: 
NAME: Tarek.M.El-Sayed 				   || 		last update:
NAME: Muhammed.Y.Abu-Tabl 			   || 		last update:

Please note that you HAVE TO write comments consistently to intrepret and clarify your code for the other team members 
so we coud easily track possible errors  

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
		int number_of_accounts = count_accounts();
		accounts *accounts_infile = load(number_of_accounts);
        if (check == 1)
        {
            printf("Welcome back\n");
            printf("\nWhat do you want to do?\nL Load account data.\nS Search.\nE Exit system.\n.T Transfer balance\n");

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
		    case 'T':
		    int sender_index=-1,receiver_index=-1;
    int sender_index=-1,receiver_index=-1;
    if(trans(accounts_infile,number_of_accounts,&sender_index,&receiver_index))
    {
    if (save(accounts_infile,number_of_accounts))
        {
            printf("Transfer successful!\nSender's new balance: %.2lf\nReceiver's new balance: %.2lf\n",
                accounts_infile[sender_index].balance,accounts_infile[receiver_index].balance);}
    else printf("Changes discarded\n");}
} break;
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
