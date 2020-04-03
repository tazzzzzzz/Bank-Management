//data.h

int i,j;
int main_exit;

struct date{
    int month,day,year;
};

typedef struct account{

    char name[60];
    int acc_no,age;
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

void start();
float interest(float t,float amount,int rate);
void fordelay(int j);
void menu();
