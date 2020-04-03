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

int valid_date(int day, int month, int year, int day1, int month1, int year1);

char* getPass();
void start();
float interest(float t,float amount,int rate);
void fordelay(int j);
void menu();
