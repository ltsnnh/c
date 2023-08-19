#include <stdio.h>
#include "common.h"

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5}, *parr = NULL;
    /* arr is a address const, a SYMBOL
    so 'arr++;' error
    */
    parr = arr;

    printf("arr[0] = %d\n", arr[0]);
    printf("arr[1] = %d\n", *(arr + 1));
    printf("arr[2] = %d\n", *(parr + 2));
    printf("arr[3] = %d\n", parr[3]);

    return 0;
}
