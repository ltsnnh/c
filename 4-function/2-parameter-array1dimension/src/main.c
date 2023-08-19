#include <stdio.h>
#include "common.h"

// int calculate(int *parr);
int calculate(int parr[]);

int main(void)
{
    int arr[] = {1, 2, 3, 4};
    int sum = 0;

    sum = calculate(arr);

    printf("sum = %d\n", sum);

    return 0;
}

int calculate(int *parr)
// int calculate(int parr[])
{
    int result = 0;
    int i = 0;

    for(i = 0; i < 4; i++)
    {
        result += *(parr + i);
    }

    return(result);
}
