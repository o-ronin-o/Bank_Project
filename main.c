/*
NAME: Omar.W.Al-Qattan 				   || 	        last update: December 21,2023
NAME: Abdallah.A.Na'eem 			   ||		last update: 
NAME: Abdelrahman.A.Abdo(7asal eh) 	           || 		last update: 
NAME: Tarek.M.El-Sayed 				   || 		last update:
NAME: Muhammed.Y.Abu-Tabl 			   || 		last update:

Please note that you HAVE TO write comments consistently to intrepret and clarify your code for the other team members 
so we coud easily track possible errors  

this is an edit 
that's a branch lolololol
3aw3aw









*/
#include <stdio.h>
#include "FUNC.h"
#include "FUNC.c"
typedef struct
{
    long long account_number;
    char name[100];
    char email[100];
    double balance;
    long long mobile;
    char date_opened[20];
} accounts;

void main(void)
{
	int choice1 = 0;
	//we need to write the script for the login here then we procceed to provide features
	while(1)
	{
		
		//you're required to complete your task presentation in the line below then procceed to write the script in the switch 
		printf("\nwhat do you want to do?\nL load account data.\nS Search.\nE Exit system.\n");
				fflush(stdin);
				scanf(" %c" , &choice1);
				choice1 = toupper(choice1);
				//switch case for the choices of the admin
				switch(choice1)
				{
					case 'L' :
							//now you can write the code here
							
					case 'S' :
							// EXTRA EXAMPLE
				}
	}
}
