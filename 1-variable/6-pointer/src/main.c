#include <stdio.h>
#include "common.h"

int main(void)
{
    int a = 0;
    int *pa = &a;
    int **ppa = &pa;

    printf("**ppa = *pa = a = %d = %d = %d\n", **ppa, *pa, a);
    putchar('\n');
    printf("pa = &a = %p = %p\n", pa, &a);
    printf("ppa = &pa = %p = %p\n", ppa, &pa);
    printf("&ppa = %p\n", &ppa);
    putchar('\n');
    printf("sizeof(a) = %ld\n", sizeof(a));
    printf("sizeof(pa) = sizeof(ppa) = %ld = %ld\n", sizeof(pa), sizeof(ppa));

    return 0;
}
