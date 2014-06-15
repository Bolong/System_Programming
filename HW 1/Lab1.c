#include <stdio.h>
#include <math.h>

void main()
{
    int array[5] = {2,9,5,4,1};

    insertionSort(array,5);

    int i;
    for (i = 0; i < 5 ; i++ )
        printf("%d",array[i]);

    printf("\narray short result:%d",isShorted(array,5));
}

void insertionSort(int array[],int arrayLength)
{
    int i,j,key;
    for (j = 1; j<arrayLength ;j++ )
    {
        key = array[j];
        i = j-1;
        while (i>=0 && array[i] > key)
        {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
    }
}

int isShorted(int array[], int arrayLength)
{
    int i;
    for (i = 0; i < arrayLength - 1; i++ )
    {
        if(array[i] >= array[i+1])
        {
            return 0;
        }
    }
    return 1;
}
