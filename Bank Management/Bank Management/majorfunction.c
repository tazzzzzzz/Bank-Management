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


void create(void){
    account check;
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
    user.deposit.day = t.wDay; 
    user.deposit.month = t.wMonth;
    user.deposit.year = t.wYear;

    
account_no:
    printf("\nPlease enter the Account Number:");
    FLUSH
    check.acc_no = getLong();
    while (fscanf(ptr, FORMAT, SCANFILE(user)) != EOF)
    {
        printf(FORMAT,PRINTFILE(user));
        if (check.acc_no == user.acc_no)
        {
            printf("Account no. already in use!");
            fseek(ptr, 0, SEEK_SET);
            goto account_no;
            break;
            fordelay(1000000000);
        }
    }

    user.acc_no = check.acc_no;

    printf("\nEnter the name:");
    scanf("%[^\n]s", user.name);
    removeSpaces(user.name);
    FLUSH

validate_dob:
    printf("\nEnter the date of birth (DD/MM/YYYY):");
    int c = 0;          /* value to test for end of input buffer */

    while ((scanf("%d/%d/%d",&user.dob.day,&user.dob.month,&user.dob.year) != 3)) 
    {
        printf("\nThe above date of birth is invalid.\nEnter a valid date of birth(mm/dd/yyyy):");
        do { c = getchar(); } while (c != '\n' && c != EOF);  /* flush input buffer */
    }
    FLUSH

    if( !(validDate(user.dob.day,user.dob.month,user.dob.year,user.deposit.day,user.deposit.month,user.deposit.year))){
        printf("Kindly enter a valid date");
        fordelay(1000000000);
        goto validate_dob;
    }
age:
    user.age = findAge(t.wDay, t.wMonth, t.wYear,user.dob.day,user.dob.month,user.dob.year);
    FLUSH

address:
    printf("\nEnter address name:");
    FLUSH
    scanf("%[^\n]s", user.address);
    removeSpaces(user.address);
    

citizenship_validation:
    printf("\nEnter the citizenship number:");
    FLUSH
    scanf("%[^\n]s", user.citizenship);
    removeSpaces(user.citizenship);
    fseek (ptr , 0 , SEEK_SET );
    while (fscanf(ptr, FORMAT, SCANFILE(check))!=EOF)
    {
        printf(FORMAT,PRINTFILE(check));

        if (!strcmp(check.citizenship,user.citizenship))
        {
            if(strcmp(check.name,user.name) || (check.dob.day!=user.dob.day) || (check.dob.month!=user.dob.month) || (check.dob.year!=user.dob.year))
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
    user.phone = phoneNumber();
    if(user.phone == -1){
        goto phone;
        FLUSH
    }
    
    

amount_to_deposit:

    printf("\nEnter the amount to deposit:$");
    FLUSH
    user.amt = getFloat();
    if(user.amt<10)
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
    scanf("%s", user.acc_type);
    removeSpaces(user.acc_type);
    FLUSH

    fprintf(ptr, FORMAT, PRINTFILE(user));

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
    while (fscanf(old, FORMAT, SCANFILE(user)) != EOF)
    {

        if (user.acc_no == transactionAccount)
        {
            test = 1;
            if (strcmpi(user.acc_type, "fixed1") == 0 || strcmpi(user.acc_type, "fixed2") == 0 || strcmpi(user.acc_type, "fixed3") == 0)
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
                user.amt +=  transactionAmount;
                fprintf(newrec, FORMAT, PRINTFILE(user));
                printf("\n\nDeposited successfully!");
            }
            else if(choice == 2)
            {
                FLUSH
                printf("\nEnter the amount you want to withdraw: $");
                 float  transactionAmount = getFloat();
                if(user.amt-10< transactionAmount)
                {
                    printf("\n\nTransaction declined. \nInsufficient Funds in account.");
                    goto transact_account;
                }  
                else
                    user.amt -=  transactionAmount;
                fprintf(newrec, FORMAT, PRINTFILE(user));
                printf("\n\nWithdrawn successfully!");
            }
        }
        else
        {
            fprintf(newrec, FORMAT, PRINTFILE(user));
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
    while (fscanf(old, FORMAT, SCANFILE(user)) != EOF)
    {
        if (user.acc_no != rem){
            // printf(FORMAT, PRINTFILE(add));
            fprintf(newrec, FORMAT, PRINTFILE(user));
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

    while(fscanf(view,FORMAT, SCANFILE(user))!=EOF)
       {
           
           printf("\n%ld\t\t %s\t\t%25.30s\t\t\t%ld",user.acc_no,user.name,user.address,user.phone);
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

    long acc_no, phone;
    char address[60];

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
    acc_no = getLong();
    while(fscanf(old,FORMAT, SCANFILE(user))!=EOF)
    {
        if (user.acc_no==acc_no)
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
                scanf("%s",address);
                fprintf(newrec,FORMAT,user.acc_no,user.name,user.dob.month,user.dob.day,user.dob.year,user.age,address,user.citizenship,user.phone,user.acc_type,user.amt,user.deposit.month,user.deposit.day,user.deposit.year);
                system("cls");
                printf("Changes saved!");
                }
            else if(choice==2)
                {
                    //Updates Phone No. Value
                    printf("Enter the new phone number:");
                    updatePhone:
                        phone = phoneNumber();
                        if(phone == -1){
                            goto updatePhone;
                            FLUSH
                        }
                fprintf(newrec,FORMAT,user.acc_no,user.name,user.dob.month,user.dob.day,user.dob.year,user.age,user.address,user.citizenship,phone,user.acc_type,user.amt,user.deposit.month,user.deposit.day,user.deposit.year);
                system("cls");
                printf("Changes saved!");
                }

        }
        else
            fprintf(newrec,FORMAT,user.acc_no,user.name,user.dob.month,user.dob.day,user.dob.year,user.age,user.address,user.citizenship,user.phone,user.acc_type,user.amt,user.deposit.month,user.deposit.day,user.deposit.year);
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

    /*
    RECOMMENDATIONS/RULES
    DCL05-A. Use typedefs to improve code readability
    */
    typedef int flag;
    typedef int option;
    //Function to view details of a particular record
    /*
    RECOMMENDATIONS/RULES
    DCL00-A. Declare immutable values using const or enum
    DCL03-A: Place const as the rightmost declaration specifier
    DCL33-C. Ensure that source and destination pointers in function arguments do not point to overlapping objects if they are restrict qualified
    */
    FILE *restrict const ptr=fopen("record.txt","r"); 
    account check;
    int errnum;
    /*
    RECOMMENDATIONS/RULES
    DCL09-A. Declare functions that return an errno with a return type of errno_t
    */
    if(ptr == NULL){
        errnum = errno;
        fprintf(stderr, "ERROR CODE: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
        exit(0);
    }
    flag test=0;
    int rate;
    option choice;
    float time;
    float intrst;
    /*
    RECOMMENDATIONS/RULES
    DCL06-A. Use meaningful symbolic constants to represent literal values in program logic
    */
    enum {RATE_FIXED1=9, RATE_FIXED2=11,RATE_FIXED3=13,RATE_SAVING=8};

    //Searches for reccord either by account number or name
    printf("Do you want to check by\n1.Account no\n2.Name\nEnter your choice:");
    FLUSH
    choice = getInt();
    if (choice==1)
    {   printf("\nEnter the account number:");
        FLUSH
        check.acc_no = getLong();

        while (fscanf(ptr,FORMAT, SCANFILE(user))!=EOF)
        {
            if(user.acc_no==check.acc_no)
            {   system("cls");
                test=1;
                //Each of the following conditions are used to determine the interest by a certain date based on the type of account
                printf("\nAccount NO.:%ld\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%ld \nType Of Account:%s \nAmount deposited: $%.2f \nDate Of Deposit:%d/%d/%d\n\n",PRINTFILE(user));
                //Fixed Accounts
                if(strcmpi(user.acc_type,"fixed1")==0)
                    {
                        time=1.0;
                        rate=RATE_FIXED1;
                        intrst=interest(time,user.amt,rate);
                        printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,user.deposit.month,user.deposit.day,user.deposit.year+1);
                    }
                else if(strcmpi(user.acc_type,"fixed2")==0)
                    {
                        time=2.0;
                        rate=RATE_FIXED2;
                        intrst=interest(time,user.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,user.deposit.month,user.deposit.day,user.deposit.year+2);

                    }
                else if(strcmpi(user.acc_type,"fixed3")==0)
                    {
                        time=3.0;
                        rate=RATE_FIXED3;
                        intrst=interest(time,user.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,user.deposit.month,user.deposit.day,user.deposit.year+3);

                    }
                //Savings Account
                 else if(strcmpi(user.acc_type,"saving")==0)
                    {
                        time=(1.0/12.0);
                        rate=RATE_SAVING;
                        intrst=interest(time,user.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,user.deposit.day);

                     }
                //Current Account
                 else if(strcmpi(user.acc_type,"current")==0)
                    {

                        printf("\n\nYou will get no interest\a\a");

                     }

            }
        }
    }
    //Search by Name
    else if (choice==2)
    {   
        printf("\nEnter the name:");
        scanf("%[^\n]s", check.name);
        removeSpaces(check.name);
        // printf("%s",user.name);
        FLUSH
        while (fscanf(ptr,FORMAT, SCANFILE(user))!=EOF)
        {
            if(strcmpi(user.name,check.name)==0){
            // {   system("cls");
                test=1;
                printf("\nAccount No.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$%.2f \nDate Of Deposit:%d/%d/%d\n\n",user.acc_no,user.name,user.dob.month,user.dob.day,user.dob.year,user.age,user.address,user.citizenship,user.phone,
                user.acc_type,user.amt,user.deposit.month,user.deposit.day,user.deposit.year);
                //Fixed Accounts
                if(strcmpi(user.acc_type,"fixed1")==0)
                    {
                        time=1.0;
                        rate=9;
                        intrst=interest(time,user.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,user.deposit.month,user.deposit.day,user.deposit.year+1);
                    }
                else if(strcmpi(user.acc_type,"fixed2")==0)
                    {
                        time=2.0;
                        rate=11;
                        intrst=interest(time,user.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,user.deposit.month,user.deposit.day,user.deposit.year+2);

                    }
                else if(strcmpi(user.acc_type,"fixed3")==0)
                    {
                        time=3.0;
                        rate=13;
                        intrst=interest(time,user.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,user.deposit.month,user.deposit.day,user.deposit.year+3);

                    }
                //Savings Account
                 else if(strcmpi(user.acc_type,"saving")==0)
                    {
                        time=(1.0/12.0);
                        rate=8;
                        intrst=interest(time,user.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,user.deposit.day);

                     }
                //Current Account
                 else if(strcmpi(user.acc_type,"current")==0)
                    {

                        printf("\n\nYou will get no interest\a\a");

                     }

            }
        }
    }

    //Incase the record wasnt found
    fclose(ptr);
     if(test!=1)
        {   system("cls");
            printf("\nRecord not found!!\a\a\a");
            see_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);
              system("cls");
                 if (main_exit==1)
                    return;
                else if (main_exit==2)
                    exit(0);
                else if(main_exit==0)
                    see();
                else
                    {
                        system("cls");
                        printf("\nInvalid!\a");
                        goto see_invalid;}
        }
    else
        {printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);}
        if (main_exit==1)
        {
            system("cls");
            return;
        }

        else
           {

             system("cls");
            exit(0);
            }


}


