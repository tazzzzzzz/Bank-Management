#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <ctype.h>
#include "data.h"
#include "inputvalidation.h"

// long getLong(){
//     char *p, s[100];
//     long n;

//     while (fgets(s, sizeof(s), stdin)) {
//         n = strtol(s, &p, 10);
//         if (p == s || *p != '\n') {
//             printf("\nPlease enter the account number: ");
//         } else break;
//     }
//     printf("You entered: %ld\n", n);
//     return n;
// }

float getFloat(){
        char buffer[100];
    double value;
    char *endptr;
    // if (fgets(buffer, sizeof(buffer) stdin) == NULL)
    //     return -1; /* Unexpected error */
    value = strtod(buffer, &endptr);
    if ((*endptr == '\0') || (isspace(*endptr) != 0)){
        printf("It's float: %f\n", value);
        return value;
    }
    else
        printf("It's NOT float ...\n");
        return 0;
}

void create()
{
    int choice;
    //int test = 0;
    FILE *ptr;

    ptr = fopen("record.txt", "a+");


    //Get Time.
    SYSTEMTIME t; 
    GetLocalTime(&t);
    printf("\n\n\nToday's date (DD/MM/YYYY): %d/%d/%d", t.wDay, t.wMonth, t.wYear);
    add.deposit.day = t.wDay; 
    add.deposit.month = t.wMonth;
    add.deposit.year = t.wYear;

    
account_no:
    system("cls");
    printf("\t\t\t ADD RECORD  ");
   
    check.acc_no = getLong();

//     printf("\nEnter the account number:");
//     scanf("%d", &check.acc_no);
    while (fscanf(ptr, FORMAT, &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (check.acc_no == add.acc_no)
        {
            printf("Account no. already in use!");
            fseek(ptr, 0, SEEK_SET);

            fordelay(1000000000);
            goto account_no;
        }
    }
    add.acc_no = check.acc_no;

    printf("\nEnter the name:");
    scanf("%[^\n]s", add.name);

    validate_dob:
    printf("\nEnter the date of birth (DD/MM/YYYY):");
    int c = 0;          /* value to test for end of input buffer */

    while ((scanf("%d/%d/%d",&add.dob.month,&add.dob.day,&add.dob.year) != 3)) 
    {
        printf("\nThe above date of birth is invalid.\nEnter a valid date of birth(mm/dd/yyyy):");
        do { c = getchar(); } while (c != '\n' && c != EOF);  /* flush input buffer */
    }

    if( !(valid_date(add.dob.day,add.dob.month,add.dob.year,add.deposit.day,add.deposit.month,add.deposit.year))){
        fordelay(1000000000);
        goto validate_dob;
    }

    add.age = findAge(t.wDay, t.wMonth, t.wYear,add.dob.day,add.dob.month,add.dob.year);

    printf("\nEnter the address:");
    scanf("%[^\n]s", add.address);

    
citizenship_validation:
    printf("\nEnter the citizenship number:");
    scanf("%s", add.citizenship);
//    printf("\nFTELL:%d",ftell(ptr));
    fseek (ptr , 0 , SEEK_SET );
 //   printf("\nFTELL:%d",ftell(ptr));
//    printf("\n%s",add.citizenship);
    while (fscanf(ptr, FORMAT, &check.acc_no, check.name, &check.dob.day, &check.dob.month, &check.dob.year, &check.age, check.address, check.citizenship, &check.phone, check.acc_type, &check.amt, &check.deposit.day, &check.deposit.month, &check.deposit.year)!=EOF)
    {
        if (!strcmp(check.citizenship,add.citizenship))
        {
            if(strcmp(check.name,add.name)){
                printf("Uh Oh! Try again with proper credentials.");   
                fordelay(1000000000);
                fseek (ptr , 0 , SEEK_SET );
                goto citizenship_validation;
            }
        }
    }
    printf("\nEnter the phone number: ");
    scanf("%lf", &add.phone);
amount_to_deposit:
    printf("\nEnter the amount to deposit:$");
    add.amt = getFloat();
    if(add.amt<=10)
    {
        printf("You need to deposit a minimum of $10.");
        goto amount_to_deposit;
    }

    printf("\nType of account: ");
    printf("\n\t-> Saving\n\t-> Current\n");
    printf("\t-> Fixed1(for 1 year)\n\t-> Fixed2(for 2 years)\n\t-> Fixed3(for 3 years)");
    printf("\n\n\tEnter your choice:");
    scanf("%s", add.acc_type);

    fprintf(ptr, FORMAT, add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

    fclose(ptr);
    printf("\nAccount created successfully!");
add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        return;
    else if (main_exit == 0)
        exit(0);
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}
void transact(void)
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");

    printf("Enter the account no. of the customer:");
    scanf("%d", &transaction.acc_no);
    while (fscanf(old, FORMAT, &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
    {

        if (add.acc_no == transaction.acc_no)
        {
            test = 1;
            if (strcmpi(add.acc_type, "fixed1") == 0 || strcmpi(add.acc_type, "fixed2") == 0 || strcmpi(add.acc_type, "fixed3") == 0)
            {
                printf("\a\a\a\n\nYou cannot deposit or withdraw cash from fixed accounts. Kindly wait until more transaction features are made available.");
                fordelay(1000000000);
                system("cls");
                return;
            }
        transact_account:
            printf("\n\nTransaction:\n1.Deposit\n2.Withdraw\nEnter your choice (1 for Deposit and 2 for Withdrawal):");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Enter the amount you want to deposit:$ ");
                scanf("%f", &transaction.amt);             
                add.amt += transaction.amt;
                fprintf(newrec, FORMAT, add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\nDeposited successfully!");
            }
            else
            {
                printf("Enter the amount you want to withdraw:$ ");
                scanf("%f", &transaction.amt);
                if(add.amt-10<transaction.amt)
                {
                    printf("Transaction declined. Insufficient Funds in accounnt.");
                    goto transact_account;
                }  
                else
                    add.amt -= transaction.amt;
                fprintf(newrec, FORMAT, add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\nWithdrawn successfully!");
            }
        }
        else
        {
            fprintf(newrec, FORMAT, add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.txt");
    rename("new.txt", "record.txt");
    if (test != 1)
    {
        printf("\n\nRecord not found!!");
    transact_invalid:
        printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            transact();
        else if (main_exit == 1)
            return;
        else if (main_exit == 2)
            exit(0);
        else
        {
            printf("\nInvalid!");
            goto transact_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            return;
        else
            exit(0);
    }

    fclose(old);
    fclose(newrec);
}

void delete(void)
{
    FILE *old, *newrec;
    int test = 0;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");
    printf("Enter the account no. of the customer you want to delete:");
    scanf("%d", &rem.acc_no);
    while (fscanf(old, FORMAT, &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
    {
        if (add.acc_no != rem.acc_no)
            fprintf(newrec, FORMAT, add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

        else
        {
            test++;
            printf("\nRecord deleted successfully!\n");
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.txt");
    rename("new.txt", "record.txt");
    if (test == 0)
    {
        printf("\nRecord not found!!\a\a\a");
    delete_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);

        if (main_exit == 1)
            return;
        else if (main_exit == 2)
            exit(0);
        else if (main_exit == 0)
            delete();
        else
        {
            printf("\nInvalid!\a");
            goto delete_invalid;
        }
    }
    
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            return;
        else
            exit(0);
    }
}
