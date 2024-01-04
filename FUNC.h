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
void transaction_record(long long account_number,double balance,int transaction_type);
int login(User *ptr);
int count_accounts();
accounts *load(int accnum);
int save(accounts *account_list,int n);
void convertDateFormat(char *inputDate, char *outputDate);
char* validate_name();
char* validate_email();
char* validate_mobile_number();
char* validate_acc_num();
double validate_balance(double current_balance);
double validate_money(double current_money);
void trans(accounts *accounts_infile,int n);
void withdraw(accounts *ptr, int acc_no);
void advanced_search(accounts *ptr,int acc_no );
void deposit(accounts *ptr, int acc_no);
void modify(accounts *accountList, int n);
void delete_account(accounts *account_list, int *accnum);
void sortByName(accounts *account_list, int accnum);
int compareDates(char *date1, char *date2);
void printMonthYearFormat(char *date);
void sortByDate(accounts *account_list, int accnum);
void sortByBalance(accounts *account_list, int accnum);
void print_sorted(accounts *account_list, int accnum);
void searchAccount(accounts *accountList, int numAccounts);
void report(accounts *accounts_infile,int n);
void add(accounts *account_list,int*accnum);
void menu (accounts*accounts_infile,int number_of_accounts);
#endif
