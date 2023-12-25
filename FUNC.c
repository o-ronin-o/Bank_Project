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
int count_accounts(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return -1;
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
