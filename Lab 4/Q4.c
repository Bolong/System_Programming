#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 1;
char c = '1';
unsigned char uc = '1';
unsigned short int usi = 1;
long l = 1;
char* s = "1";
struct myStruct
{
    int i;
    char c;
    short dd;
    long l;
    float f;
    char s[10];
};
struct myStruct sa = {1,'1',1,1,1,"1111111111"};

void main()
{
    char* p = ( char* ) &sa;
    int k,loop;
    for(  k = 0; k < 28; k++ )
        *p++ = 0x30;

    printf("value in struct.i:%d\n",sa.i);
    printf("value in struct.c:%c\n",sa.c);
    printf("value in struct.dd:%d\n",sa.dd);
    printf("value in struct.l:%d\n",sa.l);
    printf("value in struct.f:%f\n",sa.f);
    for(loop = 0; loop < strlen(sa.s);loop++)
    {
        printf("value in struct.s:%c\n",sa.s[loop]);
    }
}
