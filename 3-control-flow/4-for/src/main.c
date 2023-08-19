#include <stdio.h>
#include "common.h"

/**
 * for([expressions1]; [expressions2]; [expressions3])
 * {}
 **/

/**
 * if expressions2 are absent, its value is considered TRUE
 * out of 'for' looping is done with 'break', 'goto' or 'return'
 *
 * if there are many expressions
 * its correctness is the last expression's correctness
 *
 * for(;;) == while(1)
 **/

float arr[] = {63.2, -45.6, 70.1, 3.6, 14.5};
int n = sizeof(arr) / sizeof(float);

int main()
{
    int i= 0, j = 0;
    float c = 0;

    /* reverse the order of the array's elements  */
    for(i = 0, j = n - 1; i < j; ++i, --j)
    {
        c = arr[i];
        arr[i] = arr[j];
        arr[j] = c;
    }

    printf("Day ket qua: \n");
    for (i=0; i<n; ++i)
        printf("%8.1f", arr[i]);
    putchar('\n');

    return 0;
}