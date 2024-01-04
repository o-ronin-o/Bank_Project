#include <stdio.h>
#include "FUNC.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int check = 0, flag = 3;
    int choice1 = 0;
    User s1[100];  // Assuming you meant to declare an array of User

    // While loop for login
    while (flag)
    {
        check = login(s1);

 int number_of_accounts = count_accounts();
        accounts *accounts_infile = load(number_of_accounts);

        if (check == 1)
        {
            while (1)
            {

                printf("Welcome back\n");
                menu(accounts_infile,number_of_accounts);
            }
        }
        else if (check == 0)
        {
            printf("Invalid username or password (you have %d attempts left).\n\n",flag-1);
            flag--;
        }
    }

    return 0;
}
