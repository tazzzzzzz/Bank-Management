#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include<errno.h>
#include "data.h"

#define FORMAT "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year

extern int errno;
/*
*obvious* RECOMMENDATIONS   //Removed in final commit
DCL00-A. Declare immutable values using const or enum
DCL01-A. Do not reuse variable names in sub-scopes
DCL02-A. Use visually distinct identifiers
DCL03-A. Place const as the rightmost declaration specifier
DCL04-A. Take care when declaring more than one variable per declaration
DCL07-A. Ensure every function has a function prototype
DCL12-A. Create and use abstract data types
DCL30-C. Declare objects with appropriate storage durations
DCL32-C. Guarantee identifiers are unique

*/


//Variable 'test' has been used throughout as a flag variable to keep track of success or failure of operations
//Note that the 'test' variable is uniquely defined for each function and operates independently

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
    printf("\nACC. NO.\tNAME\t\t\tADDRESS\t\t\t\t\tPHONE\n");
    printf("________________________________________________________________________________________________________________________");

    while(fscanf(view,FORMAT)!=EOF)
       {
           
           printf("\n%6d\t %10s\t\t\t%10.25s...\t\t%.0lf",add.acc_no,add.name,add.address,add.phone);
           test++;
       }

    fclose(view);
    //Incase there are no previous records
    if (test==0)
        {   system("cls");
            printf("\nNo Records Found...\n");}

    view_list_invalid:
     printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else if(main_exit==0)
            return;
        else
        {
            printf("\nInvalid!\a");
            goto view_list_invalid;
        }
}


void edit(void)
{
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
    scanf("%d",&upd.acc_no);
    while(fscanf(old,FORMAT)!=EOF)
    {
        if (add.acc_no==upd.acc_no)
        {   test=1;
            printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):");
            scanf("%d",&choice);
            system("cls");
            if(choice==1)
                //Updates Address Value
                {printf("Enter the new address:");
                scanf("%s",upd.address);
                fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,upd.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                system("cls");
                printf("Changes saved!");
                }
            else if(choice==2)
                {
                    //Updates Phone No. Value
                    printf("Enter the new phone number:");
                scanf("%lf",&upd.phone);
                fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,upd.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                system("cls");
                printf("Changes saved!");
                }

        }
        else
            fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
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
                    menu();
                else if (main_exit==2)
                    //Handles exit operation
                    return;
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
            menu();
        else
            return;
        }
}


void see(void)
{
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
    scanf("%d",&choice);
    if (choice==1)
    {   printf("Enter the account number:");
        scanf("%d",&check.acc_no);

        while (fscanf(ptr,FORMAT)!=EOF)
        {
            if(add.acc_no==check.acc_no)
            {   system("cls");
                test=1;
                //Each of the following conditions are used to determine the interest by a certain date based on the type of account
                printf("\nAccount NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited($): %.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                //Fixed Accounts
                if(strcmpi(add.acc_type,"fixed1")==0)
                    {
                        time=1.0;
                        rate=RATE_FIXED1;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+1);
                    }
                else if(strcmpi(add.acc_type,"fixed2")==0)
                    {
                        time=2.0;
                        rate=RATE_FIXED2;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+2);

                    }
                else if(strcmpi(add.acc_type,"fixed3")==0)
                    {
                        time=3.0;
                        rate=RATE_FIXED3;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+3);

                    }
                //Savings Account
                 else if(strcmpi(add.acc_type,"saving")==0)
                    {
                        time=(1.0/12.0);
                        rate=RATE_SAVING;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,add.deposit.day);

                     }
                //Current Account
                 else if(strcmpi(add.acc_type,"current")==0)
                    {

                        printf("\n\nYou will get no interest\a\a");

                     }

            }
        }
    }
    //Search by Name
    else if (choice==2)
    {   printf("Enter the name:");
        scanf("%s",&check.name);
        while (fscanf(ptr,FORMAT)!=EOF)
        {
            if(strcmpi(add.name,check.name)==0)
            {   system("cls");
                test=1;
                printf("\nAccount No.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$%.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                //Fixed Accounts
                if(strcmpi(add.acc_type,"fixed1")==0)
                    {
                        time=1.0;
                        rate=9;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+1);
                    }
                else if(strcmpi(add.acc_type,"fixed2")==0)
                    {
                        time=2.0;
                        rate=11;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+2);

                    }
                else if(strcmpi(add.acc_type,"fixed3")==0)
                    {
                        time=3.0;
                        rate=13;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+3);

                    }
                //Savings Account
                 else if(strcmpi(add.acc_type,"saving")==0)
                    {
                        time=(1.0/12.0);
                        rate=8;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,add.deposit.day);

                     }
                //Current Account
                 else if(strcmpi(add.acc_type,"current")==0)
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
                    menu();
                else if (main_exit==2)
                    return;
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
            menu();
        }

        else
           {

             system("cls");
            return;
            }

}
