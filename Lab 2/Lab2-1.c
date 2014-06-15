#include <stdio.h>
#include <math.h>

void main(){}

int isPrime(int num)
{
    if(num < 0)
    {
        num = -num;
    }
    if(num == 0 || num == 1)
    {
        return 0;
    }
    if(num == 2 || num == 3)
    {
        return 1;
    }
    int i;
    for(i = 2; i <= sqrt(num); i++)
    {
        if(num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
