#include <stdio.h>
#include "common.h"

int main(void)
{
    char a;
    short b;
    int c;
    long d;
    float e;
    double f;

    printf("%lu\n", (unsigned long)&a % sizeof(a));
    printf("%lu\n", (unsigned long)&b % sizeof(b));
    printf("%lu\n", (unsigned long)&c % sizeof(c));
    printf("%lu\n", (unsigned long)&d % sizeof(d));
    printf("%lu\n", (unsigned long)&e % sizeof(e));
    printf("%lu\n", (unsigned long)&f % sizeof(f));

    return 0;
}
