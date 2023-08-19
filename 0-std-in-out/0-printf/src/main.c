#include <stdio.h>
#include "common.h"

int main(void)
{
    int a = 0, result = 0;
    float b = 0;

    a = -106;
    b = -19.97;

    result = printf("123456789...\n");

    printf("%d   \n", a);
    printf("%8d  \n", a);
    printf("%08d \n", a);
    printf("%-8d \n", a);
    printf("\n");
    printf("%f     \n", b);
    printf("%8.1f  \n", b);
    printf("%08.2f \n", b);
    printf("%-8.3f \n", b);
    printf("\n");
    printf("\' \n");
    printf("\" \n");
    printf("\\ \n");
    printf("\n");
    printf("%*.3f \n", 9, b);
    printf("\n");
    printf("%d \n", result);

    return 0;
}

/**
 * int printf(const char *str [,arguments]);
 *
 * return (true: number of characters out)
 *        (false: -1)
 **/
