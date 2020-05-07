
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include<errno.h>
#include <windows.h>
#include<ctype.h>
#include "data.h"
//#include "majorfunction.h"
#include "utilFunctions.h"
#include "inputValidation.h"
void loan(void)
{
    system("cls");

    printf("\nWelcome to the loan application page");
    printf("\nEligibility Criteria:\n\nIndividuals who can take a Personal Loan:\n\n\tSalaried Employees\n\tSalaried doctors\n\tEmployees of public and private limited companies\n\tGovernment sector employees including Public Sector Undertakings, Central and Local bodies\n\tMinimum age of 21 years\n\tMaximum age of 60 years at the time of maturity of the Personal Loan\n\tMinimum net monthly income Rs. 15,000");
    fordelay(1000000000);
    fordelay(1000000000);
    printf("\n\n\n\n\tPlease enter account number: ");
    FLUSH
    ln.acc_no = getLong();

     /*
    RECOMMENDATIONS/RULES
    DCL05-A. Use typedefs to improve code readability
    */

    typedef int flag;
    typedef int option;

    //Display Records as a List
    /*
    RECOMMENDATION/RULES
    DCL00-A. Declare immutable values using const or enum
    DCL03-A: Place const as the rightmost declaration specifier
    DCL33-C. Ensure that source and destination pointers in function arguments do not point to overlapping objects if they are restrict qualified
    */

    FILE *restrict const ptr = fopen("record.txt","r");

    /*``
    RECOMMENDATIONS/RULES
    DCL09-A. Declare functions that return an errno with a return type of errno_t
    */
    
    int errnum;
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
    float time, EMI;
    float intrst, min_amt;
    int criteria = 0;
    int no_of_installments = 0;
    char ch;
    char violations[100] = "";

    /*
    RECOMMENDATIONS/RULES
    DCL06-A. Use meaningful symbolic constants to represent literal values in program logic
    */
    
    //enum {RATE_FIXED1=9, RATE_FIXED2=11,RATE_FIXED3=13,RATE_SAVING=8};

    while (fscanf(ptr,FORMAT, &add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if(add.acc_no==ln.acc_no)
        {   
            strcpy(ln.name, add.name);
            strcpy(ln.acc_type, add.acc_type);
            system("cls");
            test=1;
            //Each of the following conditions are used to determine the interest by a certain date based on the type of account
            //Fixed Accounts
            if(strcmpi(ln.acc_type,"fixed1")==0)
                {
                
                rate=11;
                intrst=interest(time,add.amt,rate);
                min_amt = (float)1000;
                }
            else if(strcmpi(ln.acc_type,"fixed2")==0)
                {
                
                rate=11;
                intrst=interest(time,add.amt,rate);
                min_amt = (float)1000;

                }
            else if(strcmpi(ln.acc_type,"fixed3")==0)
            {
                
                rate=11;
                intrst=interest(time,add.amt,rate);
                min_amt = (float)1000;

            }
            //Savings Account
            else if(strcmpi(ln.acc_type,"saving")==0)
            {
                
                rate=11;
                intrst=interest(time,add.amt,rate);
                min_amt = (float)1000;

            }
            //Current Account
            else if(strcmpi(ln.acc_type,"current")==0)
            {
                rate = 11;
                intrst = 0;
                min_amt = (float)1000;
            }
            strcpy(violations,"");
            ln.age = add.age;
            if (ln.age<21 || ln.age>60){
                //Failed age criteria
                criteria += 1;
                strncat(violations,"\tFailed Age Criteria",20);
            }

            //printf("%f",add.amt);

            if (add.amt < min_amt){
                //failed minimum amount criteria
                criteria += 1;
                strncat(violations,"\n\tFailed Min Amount Criteria",50);
            }

            if (criteria != 0){
                printf("\nAccount inelligible for loan application.\nNumber of violations: %d\n\n",criteria);
                printf("\n%s\n",violations);
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
            else
            {
                SYSTEMTIME t; 
                GetLocalTime(&t);
                ln.currloan.day = t.wDay; 
                ln.currloan.month = t.wMonth;
                ln.currloan.year = t.wYear;

                printf("\nPlease Enter Loan Amount: ");
                FLUSH
                ln.amt = getFloat();
                
                inputinstallments:
                printf("\nPlease enter the number of installments (6, 12 or 24 months): ");
                no_of_installments = getInt();

                if (no_of_installments != 6 && no_of_installments!=12 && no_of_installments!=24){
                    goto inputinstallments;
                }
                
                printf("\nType of Account: %s",ln.acc_type);
                EMI = calcEMI(ln.amt, rate, no_of_installments);


                printf("\n\n\tCalculated EMI: %f",EMI);
                fordelay(1000000000);
                printf("\nApply for loan? (y/n)");
                scanf("%s",&ch);
                if (ch == 'n'){
                    printf("\nOperation canceled by user.\nreturning...");
                    fordelay(1000000000);
                    return;
                }
                else if(ch == 'y'){
                    printf("\nProcessing...");
                    FILE *restrict const loanptr = fopen("loandetails.txt","a");
                    fprintf(loanptr,"%d %s %d/%d/%d %f %f\n",ln.acc_no, ln.name, ln.currloan.day, ln.currloan.month, ln.currloan.year, ln.amt, EMI);
                    fclose(loanptr);
                    fordelay(1000000000);
                    printf("\nLoan application successfull\n");
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

            }


        }
    }
    if (test!=1){
        printf("Account not found");
        fclose(ptr);
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
} 