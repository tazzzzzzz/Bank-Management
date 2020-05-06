int i,j;
int main_exit;
#define FORMAT "\n%ld %s %d/%d/%d %d %s %s %ld %s %f %d/%d/%d\n"
#define FLUSH fflush(stdin);
#define PRINTFILE(x) (x).acc_no, (x).name, (x).dob.day, (x).dob.month, (x).dob.year, (x).age, (x).address, (x).citizenship, (x).phone, (x).acc_type, (x).amt, (x).deposit.day, (x).deposit.month, (x).deposit.year
#define SCANFILE(x)  &(x).acc_no, (x).name, &(x).dob.day, &(x).dob.month, &(x).dob.year, &(x).age, (x).address, (x).citizenship, &(x).phone, (x).acc_type, &(x).amt, &((x)).deposit.day, &(x).deposit.month, &(x).deposit.year
#define password "root"

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
account add,upd,check,ln;