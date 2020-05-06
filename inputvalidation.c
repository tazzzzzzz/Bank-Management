#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
    
//     while (fscanf(ptr, FORMAT, &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
//     {
//   //      printf("\n%d", test++);
//         if (check.acc_no == add.acc_no)
//         {
//             printf("Account no. already in use!");
//             fseek(ptr, 0, SEEK_SET);

//             fordelay(1000000000);
//             goto account_no;
//         }
//     }
//     add.acc_no = check.acc_no;

long getAcccount()
{
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