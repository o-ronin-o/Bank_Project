#include <stdio.h>
#include "FUNC.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

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
        return;
    }
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
        printf("Error: file users.txt not found.\n");
        exit(1);
    }

    int count=0;
    while (fscanf(f,"%s %s",ptr[count].username,ptr[count].password)!=EOF)
        count++;

    fclose(f);

    char username[50];
    char password[16];

    printf("Enter your username: ");
    scanf("%s", username);
    fflush(stdin);
    printf("Enter your password: ");
    scanf("%s", password);
    fflush(stdin);

    for (int i=0; i<count; i++)
    {
        if (strcmp(ptr[i].username,username)==0 && strcmp(ptr[i].password,password)==0)
        {
            printf("Login successful\n");
            return 1;
        }
    }
    return 0;
}
int count_accounts()
{
    FILE *f= fopen("accounts.txt","r");
    if (f==NULL)
    {
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
        exit(1);
    }
    accounts *list = (accounts *)malloc(accnum * sizeof(accounts));
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
            fprintf(f,"%lld,%s,%s,%.2lf,0%lld,%s\n",account_list[i].account_number,
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
void convertDateFormat(char *inputDate, char *outputDate)
{
    struct tm timeStruct;
    sscanf(inputDate, "%d-%d", &timeStruct.tm_mon, &timeStruct.tm_year);
    timeStruct.tm_mon--;
    timeStruct.tm_year -= 1900;
    strftime(outputDate, 50, "%B %Y", &timeStruct);

}
char* validate_name()
{
    printf("Enter name: ");
    char* name = malloc(100 * sizeof(char));

    if (name == NULL)
    {
        printf("Memory allocation error.\n");
        exit(1);
    }

    int i, flag, space_found = 0;

    do
    {
        flag=0;
        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = '\0';

        i = 0;
        while (name[i] != '\0')
        {
            if (!isalpha(name[i]))
            {
                if (name[i] == ' ')
                {
                    space_found = 1;
                    if (i == 0 || !isalpha(name[i + 1]))
                    {
                        space_found = 0;
                        break;
                    }
                }
                else
                {
                    flag = 1;
                    break;
                }
            }
            i++;
        }

        if (!space_found || (name[i - 1] == ' ') || flag == 1)
        {
            printf("Invalid name, Please enter a valid name: ");
        }

    }
    while (!space_found || (name[i - 1] == ' ') || flag == 1);

    return name;
}
char* validate_email()
{
    char* email = malloc(100 * sizeof(char));

    if (email == NULL)
    {
        printf("Memory allocation error.\n");
        exit(1);
    }
    printf("Enter email: ");

    int i = 0, x = 1, at_found = 0, dot_found = 0, space_found = 0;

    do
    {
        i = 0;
        do
        {
            //getchar();
            fgets(email, 100, stdin);
            email[strcspn(email, "\n")] = '\0';
            if(!isalpha(email[i]))
            {
                x = 0;
            }
        }
        while (!isalpha(email[i]) && x != 0);
        while (email[i] != '\0')
        {
            if (email[i] == '@')
            {
                at_found = 1;
                if(!isalpha(email[i+1]) || i==0)
                    at_found = 0;

            }

            if (email[i] == '.')
            {
                dot_found = 1;
                if(!isalpha(email[i+1]) || i==0)
                   dot_found = 0;
            }

            if (email[i] == ' ')
            {
                space_found = 1;
            }

            i++;
        }

        if ((email[i] == '\0') && ((!at_found) || (!dot_found) || (space_found)))
        {
            printf("Invalid email, Please enter a valid email: ");
            at_found = 0;
            dot_found = 0;
            space_found = 0;
        }

    }
    while ((email[i] == '\0') && ((!at_found) || (!dot_found) || (space_found)));

    return email;
}
char* validate_mobile_number()
{
    printf("Enter (11-digit) mobile number: ");
    int counter = 0;

    char* mobile = malloc(12 * sizeof(char));

    if (mobile == NULL)
    {
        printf("Memory allocation error.\n");
        exit(1);
    }

    int i;

    do
    {
        fgets(mobile, 12, stdin);
        mobile[strcspn(mobile, "\n")] = '\0';

        i = 0;
        while (mobile[i] != '\0')
        {
            i++;
        }

        if (i != 11)
        {
            printf("Invalid mobile number, Please enter a valid mobile number: ");
            continue;
        }

        i = 0;

        while (mobile[i] != '\0')
        {
            if (isdigit(mobile[i]))
            {
                counter++;
            }
            i++;
        }

        if (counter != 11)
        {
            printf("Mobile number must be an 11-digit number.\nPlease enter another mobile number: ");
        }

    }
    while (i != 11 || counter != 11);

    return mobile;
}
char* validate_acc_num()
{
    char* acc_num = malloc(12 * sizeof(char));
    if (acc_num == NULL)
    {
        printf("Memory allocation error.\n");
        exit(1);
    }
    printf("Enter (10-digit) account number: ");

    int i;
    while (1)
    {
        fgets(acc_num, 12, stdin);
        fflush(stdin);
        acc_num[strcspn(acc_num, "\n")] = '\0';
        for (i = 0; i < 10; i++)
        {
            if (!isdigit(acc_num[i]))
            {
                break;
            }
        }

        if (i == 10 && acc_num[i] == '\0')
        {
            break;
        }

        printf("Invalid account number, please enter a valid account number: ");
    }

    return acc_num;
}
double validate_balance(double current_balance)
{
    printf("Enter balance: ");
    char balance[100];
    double new_balance;
    int i = 0, dot_found = 0;


    do
    {
        fgets(balance, sizeof(balance), stdin);
        balance[strcspn(balance, "\n")] = '\0';

        i = 0;
        dot_found = 0;
        while (balance[i] != '\0')
        {
            if (!isdigit(balance[i]))
            {
                if (!dot_found && balance[i] == '.')
                {
                    dot_found = 1;
                }
                else
                {
                    printf("Invalid number, Please enter a valid number: ");
                    break;
                }
            }
            i++;
        }

        if (balance[i] == '\0')
        {
            // Convert the valid balance string to a double
            sscanf(balance, "%lf", &new_balance);
            return new_balance;
        }

    }
    while (1);
}
double validate_money(double current_money)
{
    printf("Enter amount of money: ");
    char balance[100];
    double new_balance;
    int i = 0, dot_found = 0;

    do
    {
        fgets(balance, sizeof(balance), stdin);
        balance[strcspn(balance, "\n")] = '\0'; // Remove newline if present

        i = 0;
        dot_found = 0;
        while (balance[i] != '\0')
        {
            if (!isdigit(balance[i]))
            {
                if (!dot_found && balance[i] == '.')
                {
                    dot_found = 1;
                }
                else
                {
                    printf("Invalid number. Please enter another number: ");
                    break;
                }
            }
            i++;
        }

        if (balance[i] == '\0')
        {
            // Convert the valid balance string to a double
            sscanf(balance, "%lf", &new_balance);
            return new_balance;
        }

    }
    while (1);
}
void trans(accounts*accounts_infile,int n)
{
    long long account1,account2;
    double amount;
    int sender=-1,receiver=-1;
    printf("Enter the sender's account number:\n ");
    char* acc_num_str = validate_acc_num();
    if (sscanf(acc_num_str, "%lld", &account1) != 1)
    {
        printf("Invalid input for account number.\n");
        free(acc_num_str);
        return;
    }
    free(acc_num_str);

    printf("Enter the receiver's account number:\n ");
    acc_num_str = validate_acc_num();
    if (sscanf(acc_num_str, "%lld", &account2) != 1)
    {
        printf("Invalid input for account number.\n");
        free(acc_num_str);
        return;
    }
    free(acc_num_str);

    printf("Enter the amount to be transfered: \n");
    if (account1==account2)
    {
        printf("duplicated input\n");
        return;
    }
    amount = validate_money(amount);
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
void withdraw(accounts *ptr, int acc_no)
{
    long long search_no;
    int withdrawal_value, x;

    char* acc_num_str = validate_acc_num();
    if (sscanf(acc_num_str, "%lld", &search_no) != 1)
    {
        printf("Invalid input for account number.\n");
        free(acc_num_str);
        return;
    }
    free(acc_num_str);
    for (int i = 0; i < acc_no; i++)
    {
        if (ptr[i].account_number == search_no)
        {
            do
            {
                printf("Enter the withdrawal value (should not exceed the balance or $10,000): \n");
                withdrawal_value=validate_money(withdrawal_value);

                if (!(withdrawal_value <= 10000 && withdrawal_value <= ptr[i].balance))
                {
                    printf("The withdrawal value exceeds the balance or $10,000\n");
                    printf("Press 1 to edit the withdrawal value or 0 to quit: ");
                    scanf("%d", &x);
                }
            }
            while (!(withdrawal_value <= 10000 && withdrawal_value <= ptr[i].balance) && x == 1);

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
                    return;
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
    printf("Enter keyword: ");
    scanf("%s",keyword);
    printf("\n");
    printf("Search results:\n");
    keyword[0] = toupper((unsigned char)keyword[0]);

    for (int i = 0; i < acc_no; i++)
    {

        if (strstr(ptr[i].name, keyword) != NULL )
        {
            char new_date[20];
            convertDateFormat(ptr[i].date_opened,new_date);
            printf("\n");
            printf("Account Number: %lld\n", ptr[i].account_number);
            printf("Name: %s\n", ptr[i].name);
            printf("Email: %s\n", ptr[i].email);
            printf("Balance: %.2f\n", ptr[i].balance);
            printf("Mobile: 0%lld\n", ptr[i].mobile);
            printf("Date Opened: %s\n", new_date);
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

    char* acc_num_str = validate_acc_num();
    if (sscanf(acc_num_str, "%lld", &search_no) != 1)
    {
        printf("Invalid input for account number.\n");
        free(acc_num_str);
        return;
    }
    free(acc_num_str);

    for (i = 0; i < acc_no; i++)
    {
        if (ptr[i].account_number == search_no)
        {
            do
            {
                printf("Enter the deposit value (should not exceed $10,000):\n ");
                deposit_value=validate_money(deposit_value);

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
    char* acc_num_str = validate_acc_num();
    if (sscanf(acc_num_str, "%lld", &acc.account_number) != 1)
    {
        printf("Invalid input for account number.\n");
        free(acc_num_str);
        fclose(f);
        return;
    }
    free(acc_num_str);

    int account_found = 0;
    for (i = 0; i < n; i++)
    {
        if (accountList[i].account_number == acc.account_number)
        {
            account_found = 1;

            char* name = validate_name();
            strcpy(acc.name, name);
            free(name);
            strcpy(accountList[i].name,acc.name);
            int j;
            accountList[i].name[0] = toupper((unsigned char)accountList[i].name[0]);
            for(j=0; j<strlen(accountList[i].name); j++)
                if (accountList[i].name[j]==' ')
                    accountList[i].name[j+1] = toupper((unsigned char)accountList[i].name[j+1]);

            char* email = validate_email();
            strcpy(acc.email, email);
            free(email);
            fflush(stdin);
            strcpy(accountList[i].email,acc.email);
            char* mobile = validate_mobile_number();
            sscanf(mobile, "%lld", &acc.mobile);
            free(mobile);
            accountList[i].mobile=acc.mobile;
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
    char* acc_num_str = validate_acc_num();
    if (sscanf(acc_num_str, "%lld", &account_to_delete) != 1)
    {
        printf("Invalid input for account number.\n");
        free(acc_num_str);
        return;
    }
    free(acc_num_str);

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
                   /* char filename[20];
                    sprintf(filename, "%lld.txt",account_to_delete);
                    if (access(filename, F_OK) != -1)
                        {
                            remove(filename);
                        }*/
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
void printMonthYearFormat(char *date)
{
    int year, month;
    sscanf(date, "%d-%d", &month, &year);

    switch(month)
    {
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
void add(accounts *account_list, int *accnum)
{
    int i;
    long long new_account_number;
    FILE *f = fopen("accounts.txt", "a+");
    if (f == NULL)
    {
        printf("File not found.\n");
        return;
    }
    char* acc_num_str = validate_acc_num();
    if (sscanf(acc_num_str, "%lld", &new_account_number) != 1)
    {
        printf("Invalid input for account number.\n");
        free(acc_num_str);
        fclose(f);
        return;
    }
    free(acc_num_str);

    for (i = 0; i < *accnum; i++)
    {
        if (account_list[i].account_number == new_account_number)
        {
            printf("Invalid account number (Duplicate).\n");
            fclose(f);
            return;
        }
    }

    account_list = realloc(account_list, (++(*accnum)) * sizeof(accounts));
    account_list[i].account_number = new_account_number;

    char* name = validate_name();
    strcpy(account_list[i].name, name);
    free(name);
    account_list[i].name[0] = toupper((unsigned char)account_list[i].name[0]);
    int j;
    for(j=0; j<strlen(account_list[i].name); j++)
        if (account_list[i].name[j]==' ')
            account_list[i].name[j+1] = toupper((unsigned char)account_list[i].name[j+1]);

    char* email = validate_email();
    strcpy(account_list[i].email, email);
    free(email);

    account_list[i].balance = validate_balance(account_list[i].balance);

    char* mobile = validate_mobile_number();
    sscanf(mobile, "%lld", &account_list[i].mobile);
    free(mobile);

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
        char filename[20];
        sprintf(filename, "%lld.txt", new_account_number);
        FILE *f_new_account = fopen(filename, "w");
        if (f_new_account == NULL)
        {
            printf("Error opening %s for writing.\n", filename);
            return;
        }
        fclose(f_new_account);
        printf("\nNew Account Details:\n\n");
        printf("Account Number: %lld\n", new_account_number);
        printf("Name: %s\n", account_list[i].name);
        printf("E-mail: %s\n", account_list[i].email);
        printf("Balance: %.2lf $\n", account_list[i].balance);
        printf("Mobile: 0%lld\n", account_list[i].mobile);
        printf("Opened: %s\n", display_date);
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
void searchAccount(accounts *accountList, int numAccounts)
{
    long long accountNumber;
    int i;
    int accountFound = 0;

    // Ask the user for the account number
    char* acc_num_str = validate_acc_num();
    if (sscanf(acc_num_str, "%lld", &accountNumber) != 1)
    {
        printf("Invalid input for account number.\n");
        free(acc_num_str);
        return;
    }
    free(acc_num_str);

    for (i = 0; i < numAccounts; i++)
    {
        if (accountList[i].account_number == accountNumber)
        {
            accountFound = 1;
            char new_date[20];
            convertDateFormat(accountList[i].date_opened,new_date);
            printf("Account Number: %lld\n", accountList[i].account_number);
            printf("Name: %s\n", accountList[i].name);
            printf("E-mail: %s\n", accountList[i].email);
            printf("Balance: %.2lf$\n", accountList[i].balance);
            printf("Mobile: 0%lld\n", accountList[i].mobile);
            printf("Date Opened: %s\n", new_date);

            break;  // No need to continue searching after finding the account
        }
    }

    // If the account is not found, print a message
    if (!accountFound)
    {
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
void menu (accounts*accounts_infile,int number_of_accounts)
{
    number_of_accounts = count_accounts();
    accounts_infile = load(number_of_accounts);
    int choice1=20;
    int againChoice;
    printf("\nMenu:\n");
    printf("1. ADD\n");
    printf("2. DELETE\n");
    printf("3. MODIFY\n");
    printf("4. SEARCH\n");
    printf("5. ADVANCED SEARCH\n");
    printf("6. WITHDRAW\n");
    printf("7. DEPOSIT\n");
    printf("8. TRANSFER\n");
    printf("9. REPORT\n");
    printf("10.PRINT\n");
    printf("11.QUIT\n");


    scanf("%d", &choice1);
    fflush(stdin);


    // Switch case for the choices of the admin
    switch (choice1)
    {
    case 1:
        do
        {
            add(accounts_infile,&number_of_accounts);
            printf("\nPress 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);

        }
        while(1);
        break;
    case 2:
        do
        {
            delete_account(accounts_infile, &number_of_accounts);
            printf("Press 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);
        }
        while(1);
        break;
    case 3:
        do
        {
            modify(accounts_infile, number_of_accounts);
            printf("Press 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);
        }
        while(1);
        break;
    case 4:
        do
        {
            searchAccount(accounts_infile, number_of_accounts);
            printf("Press 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);
        }
        while(1);
        break;
    case 5:
        do
        {
            advanced_search(accounts_infile, number_of_accounts);
            printf("Press 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);
            break;
        }
        while(1);
        break;
    case 6:
        do
        {
            withdraw(accounts_infile, number_of_accounts);
            printf("Press 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);
        }
        while(1);
        break;
    case 7:
        do
        {
            deposit(accounts_infile, number_of_accounts);
            printf("Press 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);
        }
        while(1);
        break;
    case 8:
        do
        {
            trans(accounts_infile, number_of_accounts);
            printf("Press 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);
        }
        while(1);
        break;
    case 9:
        do
        {
            report(accounts_infile,number_of_accounts);
            printf("Press 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);
        }
        while(1);
        break;
    case 10:
        do
        {
            print_sorted(accounts_infile, number_of_accounts);
            printf("Press 1 you want to go back to the menu or 0 if you want to exit : \n");
            scanf(" %d", &againChoice);
            if (againChoice == 1)
                menu(accounts_infile,number_of_accounts);
            else
                exit(1);
        }
        while(1);
        print_sorted(accounts_infile, number_of_accounts);
        break;
    case 11:
        printf("exiting the system...");
        exit(1);
    default:
        printf("Invalid option\n");
        break;
    }
}

