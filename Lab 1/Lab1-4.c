#include<stdio.h>
void printFizzBuzz(int start, int end);
int main()
{
	printFizzBuzz(1, 100);
}
void printFizzBuzz(int start, int end)
{
	int i;
	for (i=start;i<=end;i++)
	{
	    if(i%3==0&&i%5==0)
	    	printf("FizzBuzz\n");
	    else if(i%3==0)
	    	printf("Fizz\n");
	    else if(i%5==0)
	    	printf("Buzz\n");
	    else
	    	printf("%d\n",i);
	}
}
