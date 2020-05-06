#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include<ctype.h>
#include "data.h"
#include "inputValidation.h"
#include "majorfunction.h"
#include "utilFunctions.h"

//anant.h
//File so that unit testing of each function works.
void create(void){

    int choice;
    //int test = 0;
    FILE *restrict const ptr = fopen("record.txt", "a+");

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
    
    FILE *restrict const old = fopen("record.txt", "r") ;
    FILE *restrict const newrec =  fopen("new.txt", "w");

    printf("\nEnter the account no. of the customer:");
    FLUSH
    long transactionAccount;
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
                float transactionAmount = getFloat();             
                add.amt +=  transactionAmount;
                fprintf(newrec, FORMAT, PRINTFILE(add));
                printf("\n\nDeposited successfully!");
            }
            else if(choice == 2)
            {
                FLUSH
                printf("\nEnter the amount you want to withdraw: $");
                 float  transactionAmount = getFloat();
                if(add.amt-10< transactionAmount)
                {
                    printf("\n\nTransaction declined. \nInsufficient Funds in account.");
                    goto transact_account;
                }  
                else
                    add.amt -=  transactionAmount;
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

void closeAccount(void)
{
    FILE *restrict const old = fopen("record.txt", "r") ;
    FILE *restrict const newrec =  fopen("new.txt", "w");
    int test = 0;
    long rem;

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

// void transfer(void){
    
//     int choice, test = 0;
//     FILE *old, *newrec;
//     old = fopen("record.txt", "r");
//     newrec = fopen("new.txt", "w");

//     printf("\nEnter the account no. of the payer:");
//     FLUSH
// payer:
//     long payerAccount;
//     payerAccount = getLong();
//     int x = 0;

//     while (fscanf(old, FORMAT, SCANFILE(add)) != EOF)
//     {
//         printf(FORMAT,PRINTFILE(add));
//         if (payerAccount == add.acc_no)
//         {
//             if(strcmpi(add.acc_type, "fixed1") == 0 || strcmpi(add.acc_type, "fixed2") == 0 || strcmpi(add.acc_type, "fixed3") == 0){
//                 printf("\a\a\a\n\nYou cannot deposit or withdraw cash from fixed accounts. Kindly wait until more transaction features are made available.");            
//                 break;
//             }
//             else{
//                 int x = 1; 
//                 break;
//             }
//             fseek(old, 0, SEEK_SET);
//             goto payer;
//             break;
//             fordelay(1000000000);
//         }
//     }

//     while (fscanf(old, FORMAT, SCANFILE(add)) != EOF)
//     {
//         if (add.acc_no == payerAccount)
//         {
//             test = 1;
//             if (strcmpi(add.acc_type, "fixed1") == 0 || strcmpi(add.acc_type, "fixed2") == 0 || strcmpi(add.acc_type, "fixed3") == 0)
//             {
//                 printf("\a\a\a\n\nYou cannot deposit or withdraw cash from fixed accounts. Kindly wait until more transaction features are made available.");
//                 fordelay(1000000000);
//                 system("cls");
//                 return;
//             }
//         transact_account:
//             if (choice == 1)
//             {
//                 FLUSH
//                 printf("\nEnter the amount you want to deposit: $");
//                 float transactionAmount = getFloat();             
//                 add.amt +=  transactionAmount;
//                 fprintf(newrec, FORMAT, PRINTFILE(add));
//                 printf("\n\nDeposited successfully!");
//             }
//             else if(choice == 2)
//             {
//                 FLUSH
//                 printf("\nEnter the amount you want to withdraw: $");
//                  float  transactionAmount = getFloat();
//                 if(add.amt-10< transactionAmount)
//                 {
//                     printf("\n\nTransaction declined. \nInsufficient Funds in account.");
//                     goto transact_account;
//                 }  
//                 else
//                     add.amt -=  transactionAmount;
//                 fprintf(newrec, FORMAT, PRINTFILE(add));
//                 printf("\n\nWithdrawn successfully!");
//             }
//         }
//         else
//         {
//             fprintf(newrec, FORMAT, PRINTFILE(add));
//         }
//     }
//     fclose(old);
//     fclose(newrec);
//     remove("record.txt");
//     rename("new.txt", "record.txt");

//     if (test != 1)
//     {
//         printf("\n\nRecord not found!!");
//     transact_invalid:
//         printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
//         main_exit = getInt();
//         system("cls");
//         if (main_exit == 0)
//             transact();
//         else if (main_exit == 1)
//             return;
//         else if (main_exit == 2)
//             exit(0);
//         else
//         {
//             printf("\nInvalid  Input.");
//             goto transact_invalid;
//         }
//     }
//     else
//     {
//         printf("\nEnter 1 to go to the main menu and any other number to exit. ");
//         main_exit = getInt();
//         system("cls");
//         if (main_exit == 1)
//             return;
//         else
//             exit(0);
//     }
// }
//arjun.h
void view_list()
{
    /*
    RECOMMENDATIONS/RULES
    DCL05-A. Use typedefs to improve code readability
    */
    typedef int flag;
    //Display Records as a List
    /*
    RECOMMENDATION/RULES
    DCL00-A. Declare immutable values using const or enum
    DCL03-A: Place const as the rightmost declaration specifier
    DCL33-C. Ensure that source and destination pointers in function arguments do not point to overlapping objects if they are restrict qualified
    */
    FILE *restrict const view = fopen("record.txt","r");
    /*``
    RECOMMENDATIONS/RULES
    DCL09-A. Declare functions that return an errno with a return type of errno_t
    */
    int errnum;
    if(view == NULL){
        errnum = errno;
        fprintf(stderr, "ERROR CODE: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
        exit(0);
    }

    flag test=0; //Iterate Test variable to keep track of records
    system("cls");
    printf("________________________________________________________________________________________________________________________");
    printf("\nACC. NO.\tNAME\t\t\t\tADDRESS\t\t\t\t\tPHONE\n");
    printf("________________________________________________________________________________________________________________________");

    while(fscanf(view,FORMAT, SCANFILE(add))!=EOF)
       {
           
           printf("\n%ld\t\t %s\t\t%25s\t\t\t%ld",add.acc_no,add.name,add.address,add.phone);
           test++;
       }

    fclose(view);
    //Incase there are no previous records
    if (test==0)
        {   system("cls");
            printf("\nNo Records Found.\n");}

    view_list_invalid:
     printf("\n\nEnter 1 to go to the main menu and 0 to exit. ");
        main_exit = getInt();
        system("cls");
        if (main_exit==1)
            return;
        else if(main_exit==0)
            exit(0);
        else
        {
            printf("\nInvalid!\a");
            goto view_list_invalid;
        }
}


void edit(void){
    /*
    RECOMMENDATIONS/RULES
    DCL05-A. Use typedefs to improve code readability
    */
    typedef int flag;
    typedef int option;
    //Update Values in pre-existing Records
    option choice;
    flag test=0;
    /*
    RECOMMENDATIONS/RULES
    DCL00-A. Declare immutable values using const or enum
    DCL03-A: Place const as the rightmost declaration specifier
    DCL33-C. Ensure that source and destination pointers in function arguments do not point to overlapping objects if they are restrict qualified
    */
    FILE *restrict const old=fopen("record.txt","r");    
    /*
    RECOMMENDATIONS/RULES
    DCL09-A. Declare functions that return an errno with a return type of errno_t
    */
    int errnum;
    if(old == NULL){
        errnum = errno;
        fprintf(stderr, "ERROR CODE: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
        exit(0);
    }   
    FILE *restrict const newrec=fopen("new.txt","w");
    
    printf("\nEnter the account no. of the customer whose info you want to change:");
    FLUSH
    upd.acc_no = getLong();
    while(fscanf(old,FORMAT, SCANFILE(add))!=EOF)
    {
        if (add.acc_no==upd.acc_no)
        {   
            test=1;
            printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):");
            FLUSH
            choice = getInt();
            system("cls");
            if(choice==1)
                //Updates Address Value
                {printf("Enter the new address:");
                FLUSH
                scanf("%s",upd.address);
                fprintf(newrec,FORMAT,add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,upd.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                system("cls");
                printf("Changes saved!");
                }
            else if(choice==2)
                {
                    //Updates Phone No. Value
                    printf("Enter the new phone number:");
                    updatePhone:
                        upd.phone = phoneNumber();
                        if(upd.phone == -1){
                            goto updatePhone;
                            FLUSH
                        }
                fprintf(newrec,FORMAT,add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,upd.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                system("cls");
                printf("Changes saved!");
                }

        }
        else
            fprintf(newrec,FORMAT,add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
    }
    fclose(old);
    fclose(newrec);
    remove("record.txt");
    rename("new.txt","record.txt");

    if(test!=1)
    {   
        //In case of invalid search
        system("cls");
            printf("\nRecord not found!!\a\a\a");
            edit_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);
              system("cls");
                 if (main_exit==1)
                    //Handles return to main menu
                    return;
                else if (main_exit==2)
                    //Handles exit operation
                    exit(0);
                else if(main_exit==0)
                    //Handles retry condition
                    edit();
                else
                    {printf("\nInvalid!\a");
                    goto edit_invalid;}
        }
    else
        {printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            return;
        else
            exit(0);
        }
}



void see(void){

}