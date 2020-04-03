#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include "anant.h"
#include "arjun.h"
#include "data.h"

float interest(float t,float amount,int rate)
{
    float SI;
    SI=(rate*t*amount)/100.0;
    return (SI);

}

void fordelay(int j)
{   
    int i,k;
    for(i=0;i<j;i++)
         k=i;
}

int valid_date(int dd, int mm, int yy, int day, int month, int year)
{
    if(yy<1900){
        return 0;
    }
    if( (yy>year) || ((yy==year) && (mm>month)) || ((yy==year) && (mm==month) && (dd>day))){
        return 0;
    }
    
    if(mm>12){
        return 0;
    }

    if(mm==2){        
        if( ((yy%4==0) && (yy%100!=0))|| (yy%400==0)){
            if(dd>29)
                return 0;
        }
        else{
            if(dd>28)
                return 0;
        }
    }
    
    else if((mm==1) || (mm==3)  || (mm==5) || (mm==7) || (mm==8) || (mm==10) || (mm==12)){
        if(dd>31){
            return 0;
        }
    }
    
    else{
        if(dd>30){
            return 0;
        }
    }
    return 1;
}


void menu(void)
{   int choice;
    system("cls");
   //system("color 99");
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t WELCOME TO THE MAIN MENU ");
    printf("\n\n\t\t1.Create new account\n\t\t2.Update information of existing account\n\t\t3.For transactions\n\t\t4.Check the details of existing account\n\t\t5.Removing existing account\n\t\t6.View customer's list\n\t\t7.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d",&choice);

    system("cls");
    switch(choice)
    {
        case 1:new_acc();
        break;
        case 2:edit();
        break;
        case 3:transact();
        break;
        case 4:see();
        break;
        case 5:erase();
        break;
        case 6:view_list();
        break;
        case 7:return;
        break;

    }
}


void start()
{
    char pass[10],password[10]="root";
    int i=0;
    printf("\n\n\t\tEnter the password to login:");
    scanf("%s",pass);

    if (strcmp(pass,password)==0)
        {printf("\n\nPassword Match!\nLOADING");
        for(i=0;i<=6;i++)
        {
            fordelay(100000000);
            printf(".");
        }
                system("cls");
            menu();
        }
    else
        {   printf("\n\nWrong password!!\a\a\a");
            login_try:
            printf("\nEnter 1 to try again and 0 to exit:");
            scanf("%d",&main_exit);
            if (main_exit==1)
                    {

                        system("cls");
                        start();
                    }

            else if (main_exit==0)
                    {
                    system("cls");
                    return;
                    }
            else
                    {printf("\nInvalid!");
                    fordelay(1000000000);
                    system("cls");
                    goto login_try;}

        }
    return;
}