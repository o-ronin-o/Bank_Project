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
{
    int i;
    char ch;
    FILE *f;
    printf("Do you want to save changes? (y/n)\n");
    scanf(" %c", &ch);
    fflush(stdin);
    if (ch == 'y' || ch == 'Y')
    {
        f=fopen("accounts.txt","w");
        for (i=0; i<n; i++)
        {
            fprintf(f,"%lld,%s,%s,%.2lf,%lld,%s\n",account_list[i].account_number,
                    account_list[i].name,account_list[i].email,
                    account_list[i].balance,account_list[i].mobile,account_list[i].date_opened);
        }
        fclose(f);
        return 1;
    }
    else
        fclose(f);

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
            do
            {
                printf("Enter the withdrawal value (should not exceed the balance or $10,000): ");
                scanf("%d", &withdrawal_value);

                if (!(withdrawal_value <= 10000 && withdrawal_value <= ptr[i].balance))
                {
                    printf("The withdrawal value exceeds the balance or $10,000\n");
                    printf("Press 1 to edit the withdrawal value or 0 to quit: ");
                    scanf("%d", &x);
                }
            } while (!(withdrawal_value <= 10000 && withdrawal_value <= ptr[i].balance) && x == 1);

            if (withdrawal_value <= 10000 && withdrawal_value <= ptr[i].balance)
            {
                ptr[i].balance -= withdrawal_value;
                if (save(ptr, acc_no) == 1)
                {
                    printf("Successful withdrawal. New balance: $%.2f\n", ptr[i].balance);
                      transaction_record(search_no,withdrawal_value,1);

                }
                else
                {
                    printf("Quitting without making a withdrawal.\n");
                    printf("Changes will not be saved.\n");
                }
            }
            else
            {
                printf("Quitting without making a withdrawal.\n");
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
    int i,x=0;
    long long search_no;
    double deposit_value;

    printf("Enter the account number: ");
    scanf("%lld", &search_no);

    for (i = 0; i < acc_no; i++)
    {
        if (ptr[i].account_number == search_no)
        {
            do
            {
                printf("Enter the deposit value (should not exceed $10,000): ");
                scanf("%lf", &deposit_value);

                if (!(deposit_value <= 10000))
                {
                    printf("You entered an amount that exceeds $10,000\n ");
                    printf(" press 1 if you want to edit the value or press 0 to quit ");
                    scanf("%d", &x);
                }
            }
            while (!(deposit_value <= 10000) && x == 1);

            if (deposit_value <= 10000)
            {
                 ptr[i].balance += deposit_value;
                if(save(ptr,acc_no))
                {

                    printf("Deposit successful. New balance: $%.2lf\n", ptr[i].balance);
                    transaction_record(search_no, deposit_value, 2);

                }
                else
                {
                    printf("Quitting without making a deposit.\n");
                    printf("Changes will not be saved.\n");
                }
            }
            else
            {
                printf("Quitting without making a deposit.\n");
                printf("Changes will not be saved.\n");
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
            for (int i = 0; i < *accnum; i++) {
            printf("Account Number: %lld, Name: %s, Balance: %.2lf\n",
           account_list[i].account_number, account_list[i].name, account_list[i].balance);
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
void searchAccount(accounts *accountList, int numAccounts) {
    long long accountNumber;
    int i;
    int accountFound = 0;

    // Ask the user for the account number
    printf("Enter the Account Number: ");
    scanf("%lld", &accountNumber);

    // Loop through the accounts to find the specified account number
    for (i = 0; i < numAccounts; i++) {
        if (accountList[i].account_number == accountNumber) {
            accountFound = 1;

            // Print the account information in the specified format
            printf("Account Number: %lld\n", accountList[i].account_number);
            printf("Name: %s\n", accountList[i].name);
            printf("E-mail: %s\n", accountList[i].email);
            printf("Balance: %.2lf$\n", accountList[i].balance);
            printf("Mobile: 0%lld\n", accountList[i].mobile);
            printf("Date Opened: %s\n", accountList[i].date_opened);

            break;  // No need to continue searching after finding the account
        }
    }

    // If the account is not found, print a message
    if (!accountFound) {
        printf("Account with Account Number %lld not found.\n", accountNumber);
    }
}
void report(accounts *accounts_infile,int n)
{
    int i,x=1;
    long long account_number;
    char accnum[20];
    printf("Enter the account number you want a report about: ");
    scanf("%lld",&account_number);
    for (i=0; i<n; i++)   // check if the account exist //
        if(accounts_infile[i].account_number==account_number)
        {
            x=0;
            break;
        }
    if(x)
    {
        printf("The account doesn't exist\n");
        return;
    }
    //converting long long data type into array of character//
    sprintf(accnum,"%lld.txt",account_number);
    FILE *f;
    f=fopen(accnum,"r");
    if (f==NULL)
    {
        printf("The client with account number %lld hasn't made any transaction\n",account_number);
        fclose(f);
        return;
    }
    char str[50];
    char transaction[200][50];
    int number_of_transaction=0;
    while ((fgets(str,sizeof(str),f))!=NULL&& number_of_transaction<200)
    {
        strcpy(transaction[number_of_transaction],str); //putting each string read by str in a row in the transaction 2d string//
        number_of_transaction++;
    }
    if (number_of_transaction==0) //check if it's an empty text file//
    {
        printf("\nThe client with account number %lld hasn't made any transaction\n",account_number);
        fclose(f);
        return;
    }

    int num=number_of_transaction-1;
    printf("The last transactions for account %lld:\n",account_number);
    //printing last 5 transaction if there are more than five or printing all transaction if less than 5//
    for(num; num>=number_of_transaction-5&&num>=0; num--)
    {
        printf("%s",transaction[num]);
    }
    fclose(f);
}
void add(accounts *account_list,int*accnum)
{
    int i;
    long long new_account_number;
    FILE *f = fopen("accounts.txt", "a+");
    if (f == NULL)
    {
        printf("File not found.\n");
        return;
    }
    printf("Enter the account number: ");
    if (scanf("%lld", &new_account_number) != 1)
    {
        printf("Invalid input for account number.\n");
        fclose(f);
        return;
    }

    for (i=0; i<*accnum; i++)
    {
        if (account_list[i].account_number == new_account_number)
        {
            printf("Invalid account number (Duplicate).\n");
            fclose(f);
            return;
        }
    }
    account_list = realloc(account_list, (++(*accnum)) * sizeof(accounts));
    account_list[i].account_number=new_account_number;

    printf("Enter the account name: ");
    getchar();
    gets(account_list[i].name);

    printf("Enter the email: ");
    scanf("%99s", account_list[i].email);
    fflush(stdin);

    printf("Enter the balance: ");
    scanf("%lf", &account_list[i].balance);
    fflush(stdin);

    printf("Enter the phone number: ");
    scanf("%lld", &account_list[i].mobile);
    fflush(stdin);

    fseek(f, 0, SEEK_END);

    // Get the current date
    time_t current_time;
    struct tm *local_time;

// Get the current time
    current_time = time(NULL);

// Convert the current time to the local time struct
    local_time = localtime(&current_time);

// Format the date for writing to file as "MM-YYYY" (e.g., "12-2023")
    strftime(account_list[i].date_opened, sizeof(account_list[i].date_opened), "%m-%Y", local_time);

// Format the date for displaying as "Month Year" (e.g., "December 2023")
    char display_date[50];
    strftime(display_date, sizeof(display_date), "%B %Y", local_time);

    if (save(account_list, (*accnum)) == 1)
    {
        char filename[20]; // Adjust the size based on your needs
        sprintf(filename, "%lld.txt", new_account_number);
        FILE *f_new_account = fopen(filename, "w");
        if (f_new_account == NULL)
        {
            printf("Error opening %s for writing.\n", filename);
            return;
        }
        fprintf(f_new_account, "%lld,%s,%s,%.2lf,0%lld,%s\n", new_account_number, account_list[i].name, account_list[i].email, account_list[i].balance, account_list[i].mobile, account_list[i].date_opened);
        fclose(f_new_account);
        printf("\nNew Account Details:\n\n");
        printf("Account Number: %lld\n", new_account_number);
        printf("Name: %s\n", account_list[i].name);
        printf("E-mail: %s\n", account_list[i].email);
        printf("Balance: %.2lf $\n", account_list[i].balance);
        printf("Mobile: 0%lld\n", account_list[i].mobile);
        printf("Opened: %s\n", display_date); // Display in letters
    }
    else
    {
        printf("Your account was not saved.\n");
        account_list = realloc(account_list, (--(*accnum)) * sizeof(accounts));
        if (account_list == NULL)
        {
            printf("Error in reallocating memory.\n");
            fclose(f);
            return;
        }
    }

    fclose(f);
    return;
}

