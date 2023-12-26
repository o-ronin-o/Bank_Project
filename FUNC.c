/*
here we're going to write the function definitions.
we have a couple of examples here from a previous project.
we're going to delete them they're just here to clarify the purpose of the file.
*/
#include <stdio.h>
#include "FUNC.h"
#include <stdlib.h>
#include <string.h>


int login(User *ptr)
{
    //User users[100];

    FILE *f=fopen("users.txt","r");
    if (f==NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    int count=0;
    while (fscanf(f,"%s %s",ptr[count].username,ptr[count].password)!=EOF)
        count++;

    fclose(f);

    char username[50];
    char password[7];

    printf("Enter your username: ");
    scanf("%s", username);
    fflush(stdin);
    printf("Enter your 6 characters password: ");
    scanf("%6s", password);
    fflush(stdin);

    if(strlen(password)!=6)
    {
        printf("it should be 6 characters");
        return 0;
    }

    for (int i=0; i<count; i++)
    {
        if (strcmp(ptr[i].username,username)==0 && strcmp(ptr[i].password,password)==0)
        {
            printf("Login successful\n");
            return 1;
        }
    }
    printf("Invalid username or password");
    return 0;
}

int count_accounts()
{
    FILE *f= fopen("accounts.txt","r");
    if (f==NULL)
    {
        printf("Error: can not find accounts.txt");
        return 0;
    }
    int count=0;
    char ch;
    while ((ch=getc(f))!=EOF)
        if(ch=='\n')
            count++;
    fclose(f);
    return count;
}
 accounts * load(int accnum)
{
    int i;
    FILE *f;
    f=fopen("accounts.txt","r");
      if (f==NULL)
          return NULL;
    accounts *list = (accounts *)malloc(accnum * sizeof(accounts)); // Allocate memory for the array of accounts//
    if (list == NULL)
    {
        printf("Error in allocating memory.\n");
        fclose(f);
        return NULL;

    }

    int count = 0;
    int accountNumber;

    // Loop through the file, counting occurrences of the specified format
    while (fscanf(file, "%d,%*[^,\n]", &accountNumber) == 1) {
        count++;
    }

    fclose(file);

    return count;
}


int trans(accounts*accounts_infile,int n,int *sender,int *receiver)
{
    long long account1,account2;
    double amount;
    FILE *f;
    f=fopen("accounts.txt","r");
    if (f==NULL)
    {
        printf("Error: can not find accounts.txt\n");
        return 0 ;
    }
    printf("Enter the sender's account number: ");
    scanf("%lld",&account1);
    fflush(stdin);
    printf("Enter the receiver's account number: ");
    scanf("%lld",&account2);
    fflush(stdin);
    printf("Enter the amount to be transfered: ");
    scanf("%lf",&amount);
    fflush(stdin);
    //find sender's and receiver's location//
    int i;
    for (i=0;i<n;i++)
    {
        if(accounts_infile[i].account_number==account1)
            *sender=i;
        else if(accounts_infile[i].account_number==account2)
            *receiver=i;
    }
    if(*sender==-1|| *receiver==-1)
    {printf("Invalid account number(s)\n ");
    return 0;
    }
    //check if the amount to transfer is lower than the sender's balance//
    if (amount>accounts_infile[*sender].balance)
    {
        printf("Not enough balance to transfer. \n");
        return 0;
    }
    //modify the balance of the sender and the receiver//
    accounts_infile[*sender].balance-=amount;
    accounts_infile[*receiver].balance+=amount;
}

int save(accounts *account_list,int n)
{ int i;
    char ch;
      FILE *f;
    printf("Do you want to save changes? (y/n)\n");
    scanf(" %c", &ch);
    fflush(stdin);
    if (ch == 'y' || ch == 'Y')
    {f=fopen("accounts.txt","w");
    for (i=0;i<n; i++)
    {
        fprintf(f,"%lld,%s,%s,%.2lf,%lld,%s\n",account_list[i].account_number,
                account_list[i].name,account_list[i].email,
                account_list[i].balance,account_list[i].mobile,account_list[i].date_opened);
    }
                                return 1;
                                }
    else
        return 0;
}
void withdraw(accounts *ptr, int acc_no)
{
    long long search_no;
    int withdrawal_value, x;

    printf("Enter the account number: ");
    scanf("%lld", &search_no);

    for (int i = 0; i < acc_no; i++)
    {
        if (ptr[i].account_number == search_no)
        {
            printf("Enter the withdrawal value (should not exceeds the balance or 10,000$) : ");
            scanf("%d", &withdrawal_value);

            if (withdrawal_value <= 10000&&withdrawal_value<=ptr[i].balance)
            {
                ptr[i].balance -= withdrawal_value;
                if (save(ptr,acc_no)==1)
                    printf("successful withdrawal.New balance: $%.2f\n", ptr[i].balance);
                else
                {
                    printf("Quitting without making a withdraw.\n");
                    printf("Changes will not be saved.\n");
                }

            }
            else
            {
                printf("The value exceeds the balance or exceeds 10,000$\n");
                printf("Enter 1 to edit the withdraw value or 0 to quit: ");
                scanf("%d", &x);

                if (x == 1)
                {
                    printf("Enter the corrected withdraw value (should not exceeds the balance or 10,000$): ");
                    scanf("%d", &withdrawal_value);

                    if (withdrawal_value <= 10000&&withdrawal_value<=ptr[i].balance)
                    {
                        ptr[i].balance -= withdrawal_value;
                        if (save(ptr,acc_no)==1)
                            printf(" successful. New balance: $%.2f\n", ptr[i].balance);
                        else
                        {
                            printf("Quitting without making a withdraw.\n");
                            printf("Changes will not be saved.\n");
                        }

                    }
                    else
                    {
                        printf("The corrected value still exceeds the balance. Quitting.\n");
                    }
                }
                else
                {
                    printf("Quitting without making a withdraw.\n");
                }
            }

            return;
        }
    }

    printf("Account not found with account number %lld\n", search_no);
}
void advanced_search(accounts *ptr,int acc_no )
{
    char keyword[20];
    int found=0;
    printf("Enter a keyword:");
    scanf("%s",&keyword);
    printf("\n");
     printf("Search results:\n");
    for (int i = 0; i < acc_no; i++)
    {
        // Check if the keyword present or not
        if (strstr(ptr[i].name, keyword) != NULL )
        {
            printf("\n");
            printf("Account Number: %lld\n", ptr[i].account_number);
            printf("Name: %s\n", ptr[i].name);
            printf("Email: %s\n", ptr[i].email);
            printf("Balance: %.2f\n", ptr[i].balance);
            printf("Mobile: %lld\n", ptr[i].mobile);
            printf("Date Opened: %s\n", ptr[i].date_opened);
            printf("\n");

            found=1;

        }
    }

    if (found==0)
    {
        printf("No accounts found matching this keyword '%s'.\n", keyword);
    }
}
void deposit(accounts *ptr, int acc_no)
{
    long long search_no;
    int deposit_value, x;

    printf("Enter the account number: ");
    scanf("%lld", &search_no);

    for (int i = 0; i < acc_no; i++)
    {
        if (ptr[i].account_number == search_no)
        {
            printf("Enter the deposit value (should not exceed $10,000): ");
            scanf("%d", &deposit_value);

            if (deposit_value <= 10000)
            {
                ptr[i].balance += deposit_value;
                if (save(ptr,acc_no)==1)
                    printf("Deposit successful. New balance: $%.2f\n", ptr[i].balance);
                else
                {
                    printf("Quitting without making a deposit.\n");
                    printf("Changes will not be saved.\n");
                }
            }
            else
            {
                printf("The value exceeds $10,000\n");
                printf("Enter 1 to edit the deposit value or 0 to quit: ");
                scanf("%d", &x);

                if (x == 1)
                {
                    printf("Enter the corrected deposit value (should not exceed $10,000): ");
                    scanf("%d", &deposit_value);

                    if (deposit_value <= 10000)
                    {
                        ptr[i].balance += deposit_value;
                        if (save(ptr,acc_no)==1)
                            printf("Deposit successful. New balance: $%.2f\n", ptr[i].balance);
                        else
                        {
                            printf("Quitting without making a deposit.\n");
                            printf("Changes will not be saved.\n");
                        }
                    }
                    else
                    {
                        printf("The corrected value still exceeds $10,000. Quitting.\n");
                    }
                }
                else
                {
                    printf("Quitting without making a deposit.\n");
                }
            }

            return;
        }
    }

    printf("Account not found with account number %lld\n", search_no);
}
