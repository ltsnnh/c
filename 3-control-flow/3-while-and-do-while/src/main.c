#include <stdio.h>
#include "common.h"

/**
 * while(expression1 [,expressions])
 * {}
 **/

/**
 * do {}
 * while(expression1 [,expressions]);
 **/

/**
 * if there are many expressions
 * its correctness is the last expression's correctness
 **/

int main(void)
{
    int a[] = {9, 4, 7, -3, 14};
    int n = sizeof(a) / sizeof(int);
    int i = -1;

    do
        i++;
    while(a[i] >= 0 && i < n);

    if(i < n)
        printf("Phan tu am dau tien = a[%d] = %d \n", i, a[i]);
    else
        printf("Day ko co phan tu am \n");

    return 0;
}
