#ifndef _FUNC_H_
#define _FUNC_H_

typedef struct
{
    char username[50];
    char password[7];
} User;
typedef struct
{
    long long account_number;
    char name[100];
    char email[100];
    double balance;
    long long mobile;
    char date_opened[20];
} accounts;
//here in the .h file we're going to write the prototypes of our functions

int login(User *ptr);
int count_accounts();
accounts * load(int accnum);
int trans(accounts*accounts_infile,int n,int *sender,int *receiver);
int save(accounts *account_list,int n);





#endif
