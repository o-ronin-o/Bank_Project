/*
here we're going to write the function definitions.
we have a couple of examples here from a previous project.
we're going to delete them they're just here to clarify the purpose of the file.
*/
#include <stdio.h>
#include "FUNC.h"
#include <stdlib.h>
#include <string.h>


void transaction_record(long long account_number,double balance,int transaction_type)
{
    //converting long long data type into array of character//
    char accnum[20];
    sprintf(accnum,"%lld.txt",account_number);
    //opening the file.txt of the sent account number//
    FILE *f;
    f=fopen(accnum,"a+");
    if (f==NULL)
        {
            printf("Error in opening %s.txt\n",accnum);
            fclose(f);
            return;}
    switch (transaction_type)
    {
    case 1:
        fprintf(f,"withdrowed: %.2lf$\n",balance);
    break;
    case 2:
        fprintf(f,"deposited: %.2lf$\n",balance);
    }
     fclose(f);
}



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
accounts *load(int accnum)
{
    int i;
    FILE *f;
    f=fopen("accounts.txt","r");
    if (f==NULL)
    {
        printf("Error: can't find accounts.txt\n");
        return;
    }
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

void trans(accounts*accounts_infile,int n)
{
    long long account1,account2;
    double amount;
    int sender=-1,receiver=-1;
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
    for (i=0; i<n; i++)
    {
        if(accounts_infile[i].account_number==account1)
            sender=i;
        else if(accounts_infile[i].account_number==account2)
            receiver=i;
    }
    if(sender==-1|| receiver==-1)
    {
        printf("Invalid account number(s)\n ");
        return ;
    }
    //check if the amount to transfer is lower than the sender's balance//
    if (amount>accounts_infile[sender].balance)
    {
        printf("Not enough balance to transfer. \n");
        return ;
    }
    //modify the balance of the sender and the receiver//
    accounts_infile[sender].balance-=amount;
    accounts_infile[receiver].balance+=amount;
    if (save(accounts_infile,n))
    {
        printf("Transfer successful!\nSender's new balance: %.2lf$\nReceiver's new balance: %.2lf$\n",
               accounts_infile[sender].balance,accounts_infile[receiver].balance);
               transaction_record(account1,amount,1);
               transaction_record(account2,amount,2);
    }
    else printf("Changes discarded\n");

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
void modify(accounts *accountList, int n)
{
    int i;
    accounts acc;
    FILE *f = fopen("accounts.txt", "r+");
    if (f == NULL)
    {
        perror("Error opening the file");
        return;
    }
    printf("Enter your account number: ");

    if (scanf("%lld", &acc.account_number) != 1)
    {
        printf("Error reading account number.\n");
        fclose(f);
        return;
    }

    int account_found = 0;
    for (i = 0; i < n; i++)
    {
        if (accountList[i].account_number == acc.account_number)
        {
            account_found = 1;
            printf("Enter the new name: ");
            getchar();
            if (fgets(accountList[i].name, sizeof(accountList[i].name), stdin) == NULL)
            {
                printf("Error reading name.\n");
                fclose(f);
                return;
            }
            accountList[i].name[strcspn(accountList[i].name, "\n")] = '\0'; // remove trailing newline

            printf("Enter the new Email: ");
            if (scanf("%99s", accountList[i].email) != 1)
            {
                printf("Error reading email.\n");
                fclose(f);
                return;
            }
            fflush(stdin);
            printf("Enter the new phone number: ");
            if (scanf("%lld", &accountList[i].mobile) != 1)
            {
                printf("Error reading phone number.\n");
                fclose(f);
                return;
            }

            int x = save(accountList,n);
            if (x==1)
                printf("Account details modified successfully.\n");
            else
                printf("The approach was cancelled.\n");
        }
    }

    if (!account_found)
    {
        printf("Account was not found.\n");
    }

    fclose(f);
}


void delete_account(accounts *account_list, int *accnum)
{
    long long account_to_delete;
    printf("Enter the account number you want to delete: ");
    scanf("%lld", &account_to_delete);

    int found = 0; // Flag to indicate if the account is found

    for (int i = 0; i <= *accnum ; i++)
    {
        if (account_list[i].account_number == account_to_delete)
        {
            found = 1; // Account found

            if (account_list[i].balance > 0)
            {
                printf("Deletion of that account is rejected because it has a balance.\n");
            }
            else
            {
                for (int j = i; j < *accnum -1; j++)
                {
                    account_list[j] = account_list[j + 1];
                }


                // Update the file
                if (save(account_list,*accnum-1)==1)
                {
                    (*accnum)--;
                    printf("Account deleted successfully.\n");
                }
                else
                {
                    printf("Quitting without deleting the account.\n");
                    printf("Changes will not be saved.\n");
                }
            }
            break; // Stop searching after finding the account
        }
    }

    if (!found)
    {
        printf("Account not found or invalid account number entered.\n");
    }
}





void sortByName(accounts *account_list, int accnum)
{
    int i, j;
    accounts temp;

    for (i = 0; i < accnum - 1; i++)
    {
        for (j = 0; j < accnum - i - 1; j++)
        {
            // Compare names and swap if needed
            if (strcmp(account_list[j].name, account_list[j + 1].name) > 0)
            {
                // Swap accounts
                temp = account_list[j];
                account_list[j] = account_list[j + 1];
                account_list[j + 1] = temp;
            }
        }
    }
}

void printMonthYearFormat(char *date) {
    int year, month;
    sscanf(date, "%d-%d", &month, &year);

    switch(month) {
        case 1:
            printf("January");
            break;
        case 2:
            printf("February");
            break;
        case 3:
            printf("March");
            break;
        case 4:
            printf("April");
            break;
        case 5:
            printf("May");
            break;
        case 6:
            printf("June");
            break;
        case 7:
            printf("July");
            break;
        case 8:
            printf("August");
            break;
        case 9:
            printf("September");
            break;
        case 10:
            printf("October");
            break;
        case 11:
            printf("November");
            break;
        case 12:
            printf("December");
            break;
        default:
            printf("Invalid Month");
            return;
    }
    printf(" %d\n", year);
}

int compareDates(char *date1, char *date2)
{
    // Assuming date format: YYYY-MM-DD
    int year1, month1, year2, month2;

    sscanf(date1, "%d-%d", &month1, &year1);
    sscanf(date2, "%d-%d", &month2, &year2);

    // Compare the years first
    if (year1 < year2)
    {
        return -1;
    }
    else if (year1 > year2)
    {
        return 1;
    }
    else
    {
        // If years are the same, compare the months
        if (month1 < month2)
        {
            return -1;
        }
        else if (month1 > month2)
        {
            return 1;
        }
        else
        {
            return 0; // Dates are equal
        }
    }
}

void sortByDate(accounts *account_list, int accnum)
{
    int i, j;
    accounts temp;

    for (i = 0; i < accnum - 1; i++)
    {
        for (j = 0; j < accnum - i - 1; j++)
        {
            // Compare dates and swap if needed
            if (compareDates(account_list[j].date_opened, account_list[j + 1].date_opened) > 0)
            {
                // Swap accounts
                temp = account_list[j];
                account_list[j] = account_list[j + 1];
                account_list[j + 1] = temp;
            }
        }
    }
}

void sortByBalance(accounts *account_list, int accnum)
{
    int i, j;
    accounts temp;

    for (i = 0; i < accnum - 1; i++)
    {
        for (j = 0; j < accnum - i - 1; j++)
        {
            // Compare balances and swap if needed
            if (account_list[j].balance > account_list[j + 1].balance)
            {
                // Swap accounts
                temp = account_list[j];
                account_list[j] = account_list[j + 1];
                account_list[j + 1] = temp;
            }
        }
    }
}

void print_sorted(accounts *account_list, int accnum)
{

    int choice;
    printf("Choose sorting criteria:\n");
    printf("1. Sort by Name\n");
    printf("2. Sort by Date\n");
    printf("3. Sort by Balance\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        sortByName(account_list, accnum);
        break;
    case 2:
        sortByDate(account_list, accnum);
        break;
    case 3:
        sortByBalance(account_list, accnum);
        break;
    default:
        printf("Invalid choice.\n");
        return;
    }

    // Print the sorted accounts
    printf("Sorted Accounts:\n\n");
    for (int i = 0; i < accnum; i++)
    {
        printf("Account Number: %lld\n", account_list[i].account_number);
        printf("Name: %s\n", account_list[i].name);
        printf("Email: %s\n", account_list[i].email);
        printf("Balance: %.2lf$\n", account_list[i].balance);
        printf("Mobile: 0%lld\n", account_list[i].mobile);
        printf("Date Opened: ");
        printMonthYearFormat(account_list[i].date_opened);
        printf("-------------------\n");
    }
}
