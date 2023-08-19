#include <stdio.h>
#include "common.h"

/**
 * index of array can be non-integer expression (take the integer of value)
 * but can not be a float
 **/

int array1[3] = {1, 2, 3};
int array2[4][2] = {{1, 5}, {2, 6}, {3, 7}, {4, 8}};

int main(void)
{
    printf("%d \n", array1[2]);
    printf("%d \n", array1[8/3]);
    printf("%d \n", *(array1 + 2));

    printf("%d \n", array2[3][1]);
    printf("%d \n", *(*(array2 + 3) + 1));
    printf("%d \n", *((int*)array2 + (3 * 2 + 1)));

    return 0;
}
