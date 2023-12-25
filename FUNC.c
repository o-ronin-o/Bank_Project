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
    for (i=0; i<accnum; i++)
    {
        fscanf(f,"%lld,%99[^,],%99[^,],%lf,%lld,%19[^\n]",&list[i].account_number,list[i].name,list[i].email
               ,&list[i].balance,&list[i].mobile,list[i].date_opened);
    }
    fclose(f);
    return list;
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
