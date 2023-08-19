#include <stdio.h>
#include <stdalign.h>
#include "common.h"

/**
 * Ternary conditional      e1 ? e2 : e3
 *      e1 != 0 return e2
 *      e1 = 0  return e3
 *      type returned is highest type of (e2, e3)
 *
 * Sizeof                   sizeof(type)
 * Alignof                  alignof(type)           (#include <stdalign.h>)
 *                          _Alignof(type)
 **/

typedef struct
{
    char a;
    int b;
    float c;
    double d;
} data;

int main(void)
{
    int a = 5, b =8;

    printf("max a and b = %d \n", a > b ? a : b);
    printf("sizeof(data) = %ld \n", sizeof(data));
    printf("alignof(data) = %ld \n", alignof(data));
    printf("_Alignof(int) = %ld \n", _Alignof(int));

    return 0;
}
