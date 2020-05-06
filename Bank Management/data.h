int i,j;
int main_exit;
#define FORMAT "\n%ld %s %d/%d/%d %d %s %s %ld %s %f %d/%d/%d\n"
#define FLUSH fflush(stdin);

struct date{
    int month,day,year;
};

typedef struct account{

    char name[60];
    long acc_no;
    int age;
    char address[60];
    char citizenship[15];
    long phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
    struct date currloan;

}account;
account add,upd,check,rem,transaction,ln;