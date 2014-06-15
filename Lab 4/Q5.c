#include <stdio.h>

int main()
{
    char s[ ] = "absolute";
    char *p = s;
    printf("%c\n", *p++);
    *(p + 4);
    printf("%c\n",*++p);
   //line 11 has an error here, so I delete this.
    *(p + 1) = p[1] + 2;
    printf("%c\n",*++p);
    p++;
    printf("%c\n",*p++);
    p[0] = *(p + 1);
    printf("%s\n",s);
    return 0;

}
