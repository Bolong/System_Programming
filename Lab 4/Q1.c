#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i;
char c;
unsigned char uc;
unsigned short int usi;
long l;
char* s;
struct myStruct
{
    int i;
    char c;
    short dd;
    long l;
    float f;
    char s[10];
};
struct myStruct sa;

void main()
{
    printf("sizeof int:%d\n",sizeof(i));
    printf("sizeof char:%d\n",sizeof(c));
    printf("sizeof unsigned char:%d\n",sizeof(uc));
    printf("sizeof unsigned short int:%d\n",sizeof(usi));
    printf("sizeof long:%d\n",sizeof(l));
    printf("sizeof char*:%d\n",sizeof(s));
    printf("sizeof myStruct:%d\n",sizeof(sa));
    printf("It is packed");
}
