#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<string.h>


#define null -32

#define npen 0x07
#define hpen 0x70

struct Employee {
    int code;
    char*name;
    float netSalaray;
    int entered;
};

struct Employee emp[5];

void textattr(int i)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

}

 void gotoxy(int x,int y)
 {
   COORD coord={0,0};
   coord.X=x;
   coord.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }


 char* LineEditor(int x, int y, int size, char minL, char maxL)
 {
   //gotoxy(x,y);

    int x_copy = x;
   char*str;
   str = (char*)malloc(size);
   char*st = str;
   char*end = str;
   char*curr = str;
   char*bksp = str;
   int last =y;
   int exit = 0;



   while(1-exit){
        _flushall();
        char c = getch();
        char ch;
        switch(c)
        {
            //if null (Extended)
            case -32:
            case 0:
                _flushall();
                ch = getch();
                switch(ch)
                {
                    case 75: // left
                        if(st!=curr)
                        {
                            curr--;
                            x--;
                        }
                    break;
                    case 77: // right
                        if(curr!=end)
                        {
                            curr++;
                            x++;
                        }
                    break;
                    case 71: // home
                        curr = st;
                        x = x_copy;
                    break;
                    case 79: // home
                        curr = end;
                        x = last;
                    break;
                }
            break;
            //enter
            case 13:
                *curr = '\0';
                exit = 1;

            break;

            //backspace
            case 8:
                curr--;
                x--;
                end--;
                bksp = curr;
                int b=0;
                while(bksp!=end)
                {
                    *bksp= *(bksp+1);
                    gotoxy(x+b,y);
                    printf("%c",*bksp);
                    b++;
                    bksp++;
                }
                gotoxy(x+b,y);
                printf(" ");

            break;
            //real character
            default:
                if(c>=minL || c<=maxL)
                {


                    gotoxy(x,y);
                    printf("%c",c);
                    //printf("%c",*curr);
                    *curr = c;

                    if(curr == end)
                    {
                        end++;
                        last++;
                    }
                    curr++;
                    x++;
                }

            break;
        }

    }
    return str;
 }


 void newEmp(){
    int i;

    gotoxy(7,7);
    printf("index:");

    gotoxy(7,13);
    printf("code:");

    gotoxy(25,13);
    printf("name:");

    gotoxy(7,18);
    printf("net salary:");

    getch();


    gotoxy(16,7);
    scanf("%i",&i);

    if(i<= 0 || i>5) return;
    i--;
    emp[i].entered = 1;

    /*gotoxy(16,13);
    scanf("%i",&emp[i].code);*/
    emp[i].code = atoi(LineEditor(16,13,10,'0','9'));

    //gotoxy(32,13);
    _flushall();
    //gets(emp[i].name);
    emp[i].name = LineEditor(32,13,50,'A','z');


    /*gotoxy(18,18);
    scanf("%f",&emp[i].netSalaray);*/
    emp[i].netSalaray = atoi(LineEditor(18,18,10,'0','9'));
 }

void dispEmp(){
    int c=0;
    for(int i=0;i<5;i++){

    if(emp[i].entered==0) continue;


    gotoxy(7,7+(18*c));
    printf("Employee Data:");

    gotoxy(7,13+(18*c));
    printf("Code: ");

    gotoxy(16,13+(18*c));
    printf("%i",emp[i].code);

    gotoxy(25,13+(18*c));
    printf("Name: ");

    gotoxy(32,13+(18*c));
    puts(emp[i].name);

    gotoxy(7,18+(18*c));
    printf("Salary: ");

    gotoxy(18,18+(18*c));
    printf("%f",emp[i].netSalaray);

    c++;
    }
    getch();

}
int main()
{
    int current =0;
    char menu[3][10] = {"New","Display","Exit"};
    int exitflag = 0;

    do{
        textattr(npen);
        system("cls");
        for(int i=0;i<3;i++)
        {
            gotoxy(10,7+3*i);


        if(current == i){
            textattr(hpen);
        }
        else{
            textattr(npen);
        }

        _cprintf("%s",menu[i]);
        }
        char ch;
        ch= getch();
        switch(ch){
        case null:
            ch= getch();
            switch(ch){
            case 72:
                current--;
                if(current == -1) current = 2;
                break;
            case 80:
                current++;
                if(current == 3) current = 0;
                break;

            }
        break;
        case 13:
            switch(current){
            case 0:
                textattr(npen);
                system("cls");
                /*gotoxy(10,7);
                _cprintf("new");

                char x;
                x= getch();*/
                newEmp();
                break;
            case 1:
                textattr(npen);
                system("cls");
                /*gotoxy(10,7);
                _cprintf("display");
                char b ;
                b = getch();*/
                dispEmp();
                break;
            case 2:
                textattr(npen);
                system("cls");
                exitflag =1;
                break;
            }
            break;
        case 27:
            textattr(npen);
            system("cls");
            exitflag =1;
            break;
        }

    }
    while(exitflag==0);

    return 0;
}
