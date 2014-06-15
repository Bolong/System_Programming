#include <stdio.h>
#include <math.h>

void main(){
    printPrimes(1, 100);
}
void printPrimes( int start, int end ){
int i;
for (i = start; i <= end; i++){

    if (isPrime(i) == 1){
        printf("%d\n",i);
    }
}
}

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
    int j;
    for(j = 2; j <= sqrt(num); j++)
    {
        if(num % j == 0)
        {
            return 0;
        }
    }
    return 1;
}
