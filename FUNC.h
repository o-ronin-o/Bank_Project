#ifndef _FUNC_H_
#define _FUNC_H_

typedef struct
{
    char username[50];
    char password[16];
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
void transaction_record(long long account_number,double balance,int transaction_type);
accounts *load(int accnum);
void trans(accounts *accounts_infile,int n);
int save(accounts *account_list,int n);
void withdraw(accounts *ptr, int acc_no);
void advanced_search(accounts *ptr,int acc_no );
void deposit(accounts *ptr, int acc_no);
void modify(accounts *accountList, int n);
void delete_account(accounts *account_list, int *accnum);
void print_sorted(accounts *account_list, int accnum);
void sortByName(accounts *account_list, int accnum);
void printMonthYearFormat(char *date);
int compareDates(char *date1, char *date2);
void sortByDate(accounts *account_list, int accnum);
void sortByBalance(accounts *account_list, int accnum);
void searchAccount(accounts *accountList, int numAccounts);
void report(accounts *accounts_infile,int n);
void add(accounts *account_list,int*accnum);
#endif
