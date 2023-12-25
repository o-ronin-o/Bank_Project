/*
here we're going to write the function definitions.
we have a couple of examples here from a previous project.  
we're going to delete them they're just here to clarify the purpose of the file. 
*/
#include <stdio.h>
#include "FUNC.h"
#include <stdlib.h>
#include <string.h>

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

int login(void)
{
    User users[100];

    FILE *f=fopen("users.txt","r");
    if (f==NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    int count=0;
    while (fscanf(f,"%s %s",users[count].username,users[count].password)!=EOF)
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
        if (strcmp(users[i].username,username)==0 && strcmp(users[i].password,password)==0)
        {
            printf("Login successful\n");
            return 1;
        }
    }
    printf("Invalid username or password");
    return 0;
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
