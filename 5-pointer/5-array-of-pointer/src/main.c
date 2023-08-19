#include <stdio.h>
#include "common.h"

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *parr[10] = {};     /* parr type int** */
    int i = 0;

    for(i = 0; i < 10; i++)
    {
        *(parr + i) = arr + (10 - 1 - i);
    }

    for(i = 0; i < 10; i++)
    {
        printf("%d\t", **(parr + i));       /* parr type int** */
    }
    putchar('\n');

    return 0;
}
