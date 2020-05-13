
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include<errno.h>
#include <windows.h>
#include<ctype.h>
#include "data.h"
#include "utilFunctions.h"
#include "inputValidation.h"
void loan(void)
{
    typedef int flag;
    typedef int option;
    flag test=0;
    option choice;
    int rate, criteria = 0, no_of_installments = 0;
    float time, EMI, amt, intrst, min_amt;
    char ch, violations[100] = "";
    long acc_no;
    
    system("cls");

    printf("\nWelcome to the loan application page");
    printf("\nEligibility Criteria:\n\nIndividuals who can take a Personal Loan:\n\n\tSalaried Employees\n\tSalaried doctors\n\tEmployees of public and private limited companies\n\tGovernment sector employees including Public Sector Undertakings, Central and Local bodies\n\tMinimum age of 21 years\n\tMaximum age of 60 years at the time of maturity of the Personal Loan\n\tMinimum net monthly income Rs. 15,000");
    fordelay(1000000000);
    fordelay(1000000000);
    printf("\n\n\n\n\tPlease enter account number: ");
    FLUSH
    acc_no = getLong();

     /*
    RECOMMENDATIONS/RULES
    DCL05-A. Use typedefs to improve code readability
    */

    

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
    SYSTEMTIME t; 
        GetLocalTime(&t);
        
    /*
    RECOMMENDATIONS/RULES
    DCL06-A. Use meaningful symbolic constants to represent literal values in program logic
    */
    
    //enum {RATE_FIXED1=9, RATE_FIXED2=11,RATE_FIXED3=13,RATE_SAVING=8};

    while (fscanf(ptr,FORMAT, SCANFILE(user))!=EOF)
    {
        if(user.acc_no==acc_no)
        {   
            //FILE *loanptr = fopen("loandetails.txt","r");
            // while(fscanf(loanptr,"%d %s %d/%d/%d %f %f %d\n",add.acc_no, add.name, add.currloan.day, add.currloan.month, add.currloan.year, add.amt, EMI, no_of_installments)){
            //     printf("%d",no_of_installments);
            //     if(add.acc_no == acc_no && (add.currloan.year + (no_of_installments/12)) > t.wYear){
            //         printf("\nThis account already has an outstanding loan. Kindly select another account...");
            //         fordelay(1000000000);
            //         return;
            //     }
            
            // }
            // fclose(loanptr);
            system("cls");
            test=1;
            //Each of the following conditions are used to determine the interest by a certain date based on the type of account
            //Fixed Accounts
            if(strcmpi(user.acc_type,"fixed1")==0)
                {
                
                rate=11;
                intrst=interest(time,user.amt,rate);
                min_amt = (float)1000;
                }
            else if(strcmpi(user.acc_type,"fixed2")==0)
                {
                
                rate=11;
                intrst=interest(time,user.amt,rate);
                min_amt = (float)1000;

                }
            else if(strcmpi(user.acc_type,"fixed3")==0)
            {
                
                rate=11;
                intrst=interest(time,user.amt,rate);
                min_amt = (float)1000;

            }
            //Savings Account
            else if(strcmpi(user.acc_type,"saving")==0)
            {
                
                rate=11;
                intrst=interest(time,user.amt,rate);
                min_amt = (float)1000;

            }
            //Current Account
            else if(strcmpi(user.acc_type,"current")==0)
            {
                rate = 11;
                intrst = 0;
                min_amt = (float)1000;
            }
            strcpy(violations,"");
            if (user.age<21 || user.age>60){
                //Failed age criteria
                criteria += 1;
                strncat(violations,"\tFailed Age Criteria",20);
            }


            if (user.amt < min_amt){
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
                user.currloan.day = t.wDay; 
                user.currloan.month = t.wMonth;
                user.currloan.year = t.wYear;

                printf("\nPlease Enter Loan Amount: ");
                FLUSH
                amt = getFloat();
                
                inputinstallments:
                printf("\nPlease enter the number of installments (12, 24 or 48 months): ");
                no_of_installments = getInt();

                if (no_of_installments != 12 && no_of_installments!=24 && no_of_installments!=48){
                    goto inputinstallments;
                }
                
                printf("\nType of Account: %s",user.acc_type);
                EMI = calcEMI(amt, rate, no_of_installments);


                printf("\n\nCalculated EMI: %f",EMI);
                fordelay(1000000000);
                printf("\nApply for loan? (y/n): ");
                scanf("%s",&ch);
                if (ch == 'n'){
                    printf("\nOperation canceled by user.\nreturning...");
                    fordelay(1000000000);
                    return;
                }
                else if(ch == 'y'){
                    printf("\nProcessing...");
                    FILE *loanptr = fopen("loandetails.txt","a");
                    fprintf(loanptr,"%d %s %d/%d/%d %f %f %d\n",user.acc_no, user.name, user.currloan.day, user.currloan.month, user.currloan.year, amt, EMI, no_of_installments);
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