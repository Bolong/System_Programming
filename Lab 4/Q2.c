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
    printf("address of i:%p\n",&i);
    printf("address of c:%p\n",&c);
    printf("address of uc:%p\n",&uc);
    printf("address of usi:%p\n",&usi);
    printf("address of l:%p\n",&l);
    printf("address of s:%p\n",&s);
    printf("address of sa:%p\n",&sa);

}
