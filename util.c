#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include "anant.h"
#include "arjun.h"
#include "data.h"

#define ENTER 13
#define TAB 9
#define BKSP 8

// static inline float interest(float t, float amount, int rate)
// {     
// /*
//     CERT C:    
//         PRE31-C. Avoid side effects in arguments to unsafe macros
//     Secured Programming with C:
//         PRE00-C. Prefer inline or static functions to function-like macros
    
// */
//     return ((rate * t * amount) / 100.0);
// }

void fordelay(int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

int valid_date(int dd, int mm, int yy, int day, int month, int year)
{
/*
    EXP00-A. Use parentheses for precedence of operation
*/
    if (yy < 1900)
        return 0;
    if ((yy > year) || ((yy == year) && (mm > month)) || ((yy == year) && (mm == month) && (dd > day)))  
        return 0;
/*
EXP33-C. Do not reference uninitialized variables.
(All possibilities have been thoroughly considered.)
*/

    if (mm > 12)
        return 0;

    if (mm == 2)
    {
        if (((yy % 4 == 0) && (yy % 100 != 0)) || (yy % 400 == 0))
        {
            if (dd > 29)
                return 0;
        }
        else
        {
            if (dd > 28)
                return 0;
        }
    }

    else if ((mm == 1) || (mm == 3) || (mm == 5) || (mm == 7) || (mm == 8) || (mm == 10) || (mm == 12))
    {
        if (dd > 31)
            return 0;

    }

    else
    {
        if (dd > 30)
            return 0;
    }
    return 1;
}


int findAge(int current_date, int current_month, int current_year, int birth_date, int birth_month, int birth_year) 
{ 
    // days of every month 
    int month[] = { 31, 28, 31, 30, 31, 30, 31,  
                          31, 30, 31, 30, 31 }; 
  
    // if birth date is greater then current birth 
    // month then do not count this month and add 30  
    // to the date so as to subtract the date and 
    // get the remaining days 
    if (birth_date > current_date) { 
        current_date = current_date + month[birth_month - 1]; 
        current_month = current_month - 1; 
    } 
  
    // if birth month exceeds current month, then do 
    // not count this year and add 12 to the month so 
    // that we can subtract and find out the difference 
    if (birth_month > current_month) { 
        current_year = current_year - 1; 
        current_month = current_month + 12; 
    } 
  
    // calculate date, month, year 
    int calculated_date = current_date - birth_date; 
    int calculated_month = current_month - birth_month; 
    int calculated_year = current_year - birth_year; 
  
    // return the present age 
    return calculated_year;
} 

void menu(void)
{
    int choice;
menu:
    system("cls");
    //system("color 99");
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t WELCOME TO THE MAIN MENU ");
    printf("\n\n\t\t1.Create new account\n\t\t2.Update information of existing account\n\t\t3.For transactions\n\t\t4.Check the details of existing account\n\t\t5.Removing existing account\n\t\t6.View customer's list\n\t\t7.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);

    system("cls");
    switch (choice)
    {
    case 1:
        create();
        goto menu;
        break;
    case 2:
        edit();
        goto menu;
        break;
    case 3:
        transact();
        goto menu;
        break;
    case 4:
        see();
        goto menu;
        break;
    case 5:
        erase();
        goto menu;
        break;
    case 6:
        view_list();
        goto menu;
        break;
    case 7:
        return;
        break;
    }
}

void start()
{
    char pwd[10], password[10] = "root";
    int i = 0;

    int p = 0;
    char ch;

    printf("Enter your password. Hit ENTER to confirm.\n");
    printf("Password:");

    while (1)
    {
        ch = getch(); //get key

        if (ch == ENTER || ch == TAB)
        {
            pwd[p] = '\0';
            break;
        }
        else if (ch == BKSP)
        {
            if (p > 0)
            {
                p--;
                printf("\b \b"); //for backspace
            }
        }
        else
        {
            pwd[p] = ch;
            p+=1;
/*            
EXP30-C. Do not depend on order of evaluation between sequence points
*/
            printf("* \b"); //to replace password character with *
        }
    }

    if (strcmp(pwd, password) == 0)
    {
        printf("\n\nPassword Match!\nLOADING");
        for (i = 0; i <= 6; i++)
        {
            fordelay(100000000);
            printf(".");
        }
        system("cls");
        menu();
    }
    else
    {
        printf("\n\nWrong password!!\a\a\a");
    login_try:
        printf("\nEnter 1 to try again and 0 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 1)
        {

            system("cls");
            start();
        }

        else if (main_exit == 0)
        {
            system("cls");
            return;
        }
        else
        {
            printf("\nInvalid!");
            fordelay(1000000000);
            system("cls");
            goto login_try;
        }
    }
    return;
}