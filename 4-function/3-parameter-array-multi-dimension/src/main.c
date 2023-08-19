#include <stdio.h>
#include "common.h"

// int calculate(int parr[][3]);
int calculate(int (*parr)[3]);

int main(void)
{
    int arr[][3] = {{1, 2, 3}, {4, 5, 6}};
    int sum = 0;

    sum = calculate(arr);

    printf("sum = %d\n", sum);

    return 0;
}

int calculate(int parr[][3])
// int calculate(int (*parr)[3])
{
    int result = 0;
    int i = 0, j = 0;

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 3; j++)
        {
            result += parr[i][j];
        }
    }

    return(result);
}
