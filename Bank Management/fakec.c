#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "data.h"
#include "inputValidation.h"
#include "majorfunction.h"
#include "utilFunctions.h"

//anant.h
//File so that unit testing of each function works.
void create(){

    int choice;
    //int test = 0;
    FILE *ptr;

    ptr = fopen("record.txt", "a+");

    FLUSH
    system("cls");
    printf("\t\t\t ADD RECORD  ");
    //Get Time.
    SYSTEMTIME t; 
    GetLocalTime(&t);
    printf("\n\n\nToday's date (DD/MM/YYYY): %d/%d/%d", t.wDay, t.wMonth, t.wYear);
    add.deposit.day = t.wDay; 
    add.deposit.month = t.wMonth;
    add.deposit.year = t.wYear;

    
account_no:
    printf("\nPlease enter the Account Number:");
    FLUSH
    check.acc_no = getLong();
    while (fscanf(ptr, FORMAT, SCANFILE(add)) != EOF)
    {
        printf(FORMAT,PRINTFILE(add));
        if (check.acc_no == add.acc_no)
        {
            printf("Account no. already in use!");
            fseek(ptr, 0, SEEK_SET);
            goto account_no;
            break;
            fordelay(1000000000);
        }
    }

    add.acc_no = check.acc_no;

    printf("\nEnter the name:");
    scanf("%[^\n]s", add.name);
    removeSpaces(add.name);
    // printf("%s",add.name);
    FLUSH

validate_dob:
    printf("\nEnter the date of birth (DD/MM/YYYY):");
    int c = 0;          /* value to test for end of input buffer */

    while ((scanf("%d/%d/%d",&add.dob.day,&add.dob.month,&add.dob.year) != 3)) 
    {
        printf("\nThe above date of birth is invalid.\nEnter a valid date of birth(mm/dd/yyyy):");
        do { c = getchar(); } while (c != '\n' && c != EOF);  /* flush input buffer */
    }
    FLUSH

    if( !(validDate(add.dob.day,add.dob.month,add.dob.year,add.deposit.day,add.deposit.month,add.deposit.year))){
        printf("Kindly enter a valid date");
        fordelay(1000000000);
        goto validate_dob;
    }
age:
    add.age = findAge(t.wDay, t.wMonth, t.wYear,add.dob.day,add.dob.month,add.dob.year);
    FLUSH

address:
    printf("\nEnter address name:");
    FLUSH
    scanf("%[^\n]s", add.address);
    removeSpaces(add.address);
    

citizenship_validation:
    printf("\nEnter the citizenship number:");
    FLUSH
    scanf("%[^\n]s", add.citizenship);
    removeSpaces(add.citizenship);
    fseek (ptr , 0 , SEEK_SET );
    while (fscanf(ptr, FORMAT, SCANFILE(check))!=EOF)
    {
        printf(FORMAT,PRINTFILE(check));

        if (!strcmp(check.citizenship,add.citizenship))
        {
            if(strcmp(check.name,add.name) || (check.dob.day!=add.dob.day) || (check.dob.month!=add.dob.month) || (check.dob.year!=add.dob.year))
            {
                printf("Uh Oh! Try again with proper credentials.");   
                fordelay(1000000000);
                fseek (ptr , 0 , SEEK_SET );
                goto citizenship_validation;
            }

        }
    }
    FLUSH

phone:
    printf("\nEnter the phone number: ");
    FLUSH
    add.phone = phoneNumber();
    if(add.phone == -1){
        goto phone;
        FLUSH
    }
    
    

amount_to_deposit:

    printf("\nEnter the amount to deposit:$");
    FLUSH
    add.amt = getFloat();
    if(add.amt<=10)
    {
        printf("You need to deposit a minimum of $10.");
        goto amount_to_deposit;
    }
    FLUSH

account_type:
    printf("\nType of account: ");
    printf("\n\t-> Saving\n\t-> Current\n");
    printf("\t-> Fixed1(for 1 year)\n\t-> Fixed2(for 2 years)\n\t-> Fixed3(for 3 years)");
    printf("\n\n\tEnter your choice:");
    scanf("%s", add.acc_type);
    removeSpaces(add.acc_type);
    FLUSH

    fprintf(ptr, FORMAT, PRINTFILE(add));

    fclose(ptr);
    printf("\nAccount created successfully!");
add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    main_exit = getInt();
    if (main_exit == 1)
    {
        system("cls");
        return;
    }
    else if (main_exit == 0){
        system("cls");
        exit(0);
    
    }
    
    else
    {
        printf("\nInvalid!\a");
        system("cls");
        goto add_invalid;
    }
}

void transact(void){

    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");

    long transactionAccount;

    printf("\nEnter the account no. of the customer:");
    FLUSH
    transactionAccount = getLong();
    while (fscanf(old, FORMAT, SCANFILE(add)) != EOF)
    {

        if (add.acc_no == transactionAccount)
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
            printf("\n\nTransaction:\n\n1: Deposit \n2: Withdrawal \nAny other number: Exit. \n\nEnter your choice :");
            choice = getInt();
            if (choice == 1)
            {
                FLUSH
                printf("\nEnter the amount you want to deposit: $");
                float transactionAmt = getFloat();             
                add.amt += transactionAmt;
                fprintf(newrec, FORMAT, PRINTFILE(add));
                printf("\n\nDeposited successfully!");
            }
            else if(choice == 2)
            {
                FLUSH
                printf("\nEnter the amount you want to withdraw: $");
                float transactionAmt = getFloat();
                if(add.amt-10<transactionAmt)
                {
                    printf("\n\nTransaction declined. \nInsufficient Funds in account.");
                    goto transact_account;
                }  
                else
                    add.amt -= transactionAmt;
                fprintf(newrec, FORMAT, PRINTFILE(add));
                printf("\n\nWithdrawn successfully!");
            }
        }
        else
        {
            fprintf(newrec, FORMAT, PRINTFILE(add));
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
        main_exit = getInt();
        system("cls");
        if (main_exit == 0)
            transact();
        else if (main_exit == 1)
            return;
        else if (main_exit == 2)
            exit(0);
        else
        {
            printf("\nInvalid  Input.");
            goto transact_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and any other number to exit. ");
        main_exit = getInt();
        system("cls");
        if (main_exit == 1)
            return;
        else
            exit(0);
    }
}

void transfers(void){
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");

 
}

void closeAccount(void)
{
    FILE *old, *newrec;
    int test = 0;
    long rem;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");
    printf("\nEnter the account no. of the customer you want to delete:");
    FLUSH
    rem = getLong();

    // printf("%ld is going to be deleted. ",rem);
    while (fscanf(old, FORMAT, SCANFILE(add)) != EOF)
    {
        if (add.acc_no != rem){
            // printf(FORMAT, PRINTFILE(add));
            fprintf(newrec, FORMAT, PRINTFILE(add));
        }

        else
        {
            test++;
            printf("\nRecord located.\n");
        }
    }

    fclose(old);
    fclose(newrec);

    if (test == 0)
    {
        printf("\nRecord not found.\a\a\a");
    
    delete_invalid:
        printf("\nEnter 0 to try deleting another record, 1 to return to main menu, 2 to exit. ");
        main_exit = getInt();

        if (main_exit == 1)
            return;
        else if (main_exit == 2)
            exit(0);
        else if (main_exit == 0)
            closeAccount();
        else
        {
            printf("\nInvalid! Kindly input a valid option.\a");
            goto delete_invalid;
        }
    }
    
    else
    {
        int choice;
        printf("\nYou need to login before you can delete.");

        int loginStatus = passwordAuthentication();

        if(loginStatus){

            remove("record.txt");
            rename("new.txt", "record.txt");
        }
        else{
            remove("new.txt");
            printf("\nSorry, you're not authorized to delete records at this moment.");
        }

        printf("\nEnter 1 to go to the main menu and any other number to exit. ");
        main_exit = getInt();
        system("cls");
        if (main_exit == 1)
            return;
        else
            exit(0);
    }
}



//arjun.h
void view_list(){
return;
}

void edit(void){
return;
}

void see(void){

}