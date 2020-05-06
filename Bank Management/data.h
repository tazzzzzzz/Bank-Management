int i,j;
int main_exit;
#define FORMAT "%ld %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n"

struct date{
    int month,day,year;
};

typedef struct account{

    char name[60];
    long acc_no;
    int age;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;

}account;
account add,upd,check,rem,transaction;