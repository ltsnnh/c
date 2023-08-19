#include <stdio.h>
#include "common.h"

/**
 * Subscript        a[i]
 *                  a<:i:>
 * Indirection      *pt
 * Address of       &a
 **/

/** Structure
 * Reference        a.b
 * Dereference      pt->b
 **/

int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};

    printf("arr[0] = %d \n", arr[0]);
    printf("arr[2] = %d \n", arr<:2:>);
    printf("arr[3] = %d \n", *(arr + 3));
    printf("arr[4] = %d \n", *(&arr[0] + 4));

    return 0;
}
