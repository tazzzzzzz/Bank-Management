#include "inputValidation.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

int getInt(){
    int num = 0, ch;
    do{
        ch = getch();
        if(ch>=48&&ch<=57){
            printf("%c",ch);
            num=num*10+(ch-48);
        }
        if(ch == 13){
            break;
        }
    }while(1);
    return num;
}

long getLong(){
    char *p, s[100];
    long n;

    while (fgets(s, sizeof(s), stdin)) {
        n = strtol(s, &p, 10);
        if (p == s || *p != '\n') {
            printf("\nPlease enter the account number: ");
        } else break;
    }
    printf("You entered: %ld\n", n);
    return n;
}

float getFloat(){
    char buffer[100];
    double value;
    char *endptr;

    getFloatValue:
    if (fgets(buffer, sizeof(buffer), stdin) == NULL){
        fflush(stdin);
        goto getFloatValue;
    }

    value = strtod(buffer, &endptr);
    if ((*endptr == '\0') || (isspace(*endptr) != 0)){
        return value;
    }
    else
        goto getFloatValue;
}

/*
    EXP00-A. Use parentheses for precedence of operation

    EXP33-C. Do not reference uninitialized variables.
    (All possibilities have been thoroughly considered.)
*/
int valid_date(int dd, int mm, int yy, int day, int month, int year)
{
    
    if (yy < 1900)
        return 0;
    if ((yy > year) || ((yy == year) && (mm > month)) || ((yy == year) && (mm == month) && (dd > day)))
        return 0;
  
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

int Check_Email_Addr(const char *address)
{
    int count = 0;
    const char *c, *domain;
    static char *rfc822_specials = "()<>@,;:\\\"[]";
    /* first we validate the name portion (name@domain) */
    for (c = address; *c; c++)
    {
        if (*c == '\"' && (c == address || *(c - 1) == '.' || *(c - 1) == '\"'))
        {
            while (*++c)
            {
                if (*c == '\"')
                    break;
                if (*c == '\\' && (*++c == ' '))
                    continue;
                if (*c <= ' ' || *c >= 127)
                    return 0;
            }
            if (!*c++)
                return 0;
            if (*c == '@')
                break;
            if (*c != '.')
                return 0;
            continue;
        }
        if (*c == '@')
            break;
        if (*c <= ' ' || *c >= 127)
            return 0;
        if (strchr(rfc822_specials, *c))
            return 0;
    }
    if (c == address || *(c - 1) == '.')
        return 0;
    /* next we validate the domain portion (name@domain) */
    if (!*(domain = ++c))
        return 0;
    do
    {
        if (*c == '.')
        {
            if (c == domain || *(c - 1) == '.')
                return 0;
            count++;
        }
        if (*c <= ' ' || *c >= 127)
            return 0;
        if (strchr(rfc822_specials, *c))
            return 0;
    } while (*++c);
    return (count >= 1);
}