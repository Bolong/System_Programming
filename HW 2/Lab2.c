#include <stdio.h>
#include <stdlib.h>

void main()
{
    //char* s = "La Roche College";
    char s[]= "La Roche College";
    int num;
    num = replace(s);
    printf("now s is:%s\nreplace %d spaces",s,num);
}

int replace(char* s)
{
    int num = 0,i,len = strlen(s);
    for(i=0 ; i<len ; i++)
    {
        if(s[i] == ' ')
        {
            s[i] = '-';
            num++;
        }
    }
    return num;
}
