#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include "data.h"


void create()

{
    int choice;
    FILE *ptr;

    ptr=fopen("record.txt","a+");
    account_no:
    system("cls");
        //Get Time.
    SYSTEMTIME t; 
    GetLocalTime(&t);
    printf("\n\n\nToday's date (DD/MM/YYYY): %d/%d/%d", t.wDay, t.wMonth, t.wYear);
    add.deposit.day = t.wDay; 
    add.deposit.month = t.wMonth;
    add.deposit.year = t.wYear;
    printf("\nEnter the account number:");
    scanf("%d",&check.acc_no);
    while(fscanf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (check.acc_no==add.acc_no)
            {printf("Account no. already in use!");
            fordelay(1000000000);
                goto account_no;

            }
    }
    add.acc_no=check.acc_no;
        printf("\nEnter the name:");
    scanf("%s",add.name);
    printf("\nEnter the date of birth(dd/mm/yyyy):");
    scanf("%d/%d/%d",&add.dob.day,&add.dob.month,&add.dob.year);
    //printf("\nEnter the age:");
    add.age = add.deposit.year - add.dob.year;
    //scanf("%d",&add.age);
    printf("\nEnter the address:");
    scanf("%s",add.address);
    printf("\nEnter the citizenship number:");
    scanf("%s",add.citizenship);
    printf("\nEnter the phone number: ");
    scanf("%lf",&add.phone);
    printf("\nEnter the amount to deposit:$");
    scanf("%f",&add.amt);
    printf("\nType of account(Please type in the complete text):\n\t#Saving ('saving')\n\t#Current ('current')\n\t#Fixed1(for 1 year) ('fixed1')\n\t#Fixed2(for 2 years) ('fixed2')\n\t#Fixed3(for 3 years) ('fixed3')\n\n\tEnter your choice:");
    scanf("%s",add.acc_type);
        
        fprintf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);


    fclose(ptr);
    printf("\nAccount created successfully!");
    add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d",&main_exit);
    system("cls");
    if (main_exit==1)
        menu();
    else if(main_exit==0)
            return;
    else
        {
            printf("\nInvalid!\a");
            goto add_invalid;
        }
}
// void create()
// {
//     int choice;
//     FILE *ptr;

//     ptr = fopen("record.txt", "a+");
    

// account_no:
//     system("cls");
//     printf("\t\t\t ADD RECORD  ");
    
//     //Get Time.
//     SYSTEMTIME t; 
//     GetLocalTime(&t);
//     printf("\n\n\nToday's date (DD/MM/YYYY): %d/%d/%d", t.wDay, t.wMonth, t.wYear);
//     add.deposit.day = t.wDay; 
//     add.deposit.month = t.wMonth;
//     add.deposit.year = t.wYear;
    

//     //Validate Account Number Entered.
//     printf("\nEnter the account number:");
//     scanf("%d", &check.acc_no);
//     while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
//     {
//         if (check.acc_no == add.acc_no)
//         {
//             printf("Account no. already in use. Try again with a different account number.");
//             fseek ( ptr , 0 , SEEK_SET );
//             fordelay(1000000000);
//             goto account_no;
//         }
//     }

//     add.acc_no = check.acc_no;

//     printf("\nEnter the name:");
//     scanf("%s", add.name);

// validate_dob:
//     printf("\nEnter the date of birth (DD/MM/YYYY):");
//     scanf("%d/%d/%d", &add.dob.day, &add.dob.month, &add.dob.year);
//     if( !(valid_date(add.dob.day,add.dob.month,add.dob.year,add.deposit.day,add.deposit.month,add.deposit.year))){
//         fseek ( ptr , 0 , SEEK_SET );
//         fordelay(1000000000);
//         goto validate_dob;
//     }
        
//     /* if(add.dob.year){
//         CODE FOR CALCULATING AGE
//      }*/

//     printf("\nEnter the Address:");
//     scanf("%s", add.address);

// citizenship_validation:
//     printf("\nEnter the citizenship number:");
//     scanf("%s", check.citizenship);
//     printf("\nFTELL:%d",ftell(ptr));
//     fseek (ptr , 0 , SEEK_SET );
//     printf("\nFTELL:%d",ftell(ptr));
//     printf("\n%s",check.citizenship);
//     while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
//     {
//         if (!strcmp(check.citizenship,add.citizenship))
//         {
//             if(strcmp(check.name,add.name)){
//                 printf("Uh Oh! Try again with proper credentials.");   
//                 fordelay(1000000000);
//                 fseek (ptr , 0 , SEEK_SET );
//                 goto citizenship_validation;
//             }
//         }
//     }

//     strcpy(add.citizenship,check.citizenship);
//     printf("\nEnter the phone number: ");
//     scanf("%lf", &add.phone);

// amount_to_deposit:
//     printf("\nEnter the amount to deposit: $");
//     scanf("%f", &add.amt);
//     if(add.amt<=10)
//     {
//         printf("You need to deposit a minimum of $10.");
//         goto amount_to_deposit;
//     }
      
      

//     printf("\nType of account: ");
//     printf("\n\t-> Saving\n\t-> Current\n");
//     printf("\t-> Fixed1(for 1 year)\n\t-> Fixed2(for 2 years)\n\t-> Fixed3(for 3 years)");
//     printf("\n\n\tEnter your choice:");
//     scanf("%s", add.acc_type);

//     fprintf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
//     fclose(ptr);
//     printf("\nAccount created successfully!");

// add_invalid:
//     printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit: ");
//     scanf("%d", &main_exit);
//     system("cls");
//     if (main_exit == 1)
//         menu();
//     else if (main_exit == 0)
//         return;
//     else
//     {
//         printf("\nInvalid Input. Please Enter a 0 or a 1.\a");
//         goto add_invalid;
//     }
// }

void transact(void)
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");

    printf("Enter the account no. of the customer:");
    scanf("%d", &transaction.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
    {

        if (add.acc_no == transaction.acc_no)
        {
            test = 1;
            if (strcmpi(add.acc_type, "fixed1") == 0 || strcmpi(add.acc_type, "fixed2") == 0 || strcmpi(add.acc_type, "fixed3") == 0)
            {
                printf("\a\a\a\n\nYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");
                fordelay(1000000000);
                system("cls");
                menu();
            }
            printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Enter the amount you want to deposit:$ ");
                scanf("%f", &transaction.amt);
                add.amt += transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\nDeposited successfully!");
            }
            else
            {
                printf("Enter the amount you want to withdraw:$ ");
                scanf("%f", &transaction.amt);
                add.amt -= transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\nWithdrawn successfully!");
            }
        }
        else
        {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
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
            menu();
        else if (main_exit == 2)
            return;
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
            menu();
        else
            return;
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
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
    {
        if (add.acc_no != rem.acc_no)
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

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
            menu();
        else if (main_exit == 2)
            return;
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
            menu();
        else
            return;
    }
}