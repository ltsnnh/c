#include <stdio.h>
#include "common.h"

typedef int nguyen;
typedef float mt50pt[50];
typedef enum {T1, T2, T3} sngoinho;

int main(void)
{
    nguyen a = 0;
    mt50pt b = {};
    sngoinho T5 = 0;

    a = 1;
    *(b + 3) = 9.7;
    T5 = 6;

    printf("a = %d \n", a);
    printf("b = %.1f \n", b[3]);
    printf("T3 = %d \n", T3);
    printf("T5 = %d \n", T5);

    return 0;
}
