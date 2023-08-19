#include <stdio.h>
#include "common.h"

int main(void)
{
    char c = 'A';
    int i = 123;
    char *pc = NULL;
    int *pi = NULL;

    pc = &c;
    pi = &i;

    printf("c = %c\n", *pc);
    printf("i = %d\n", *pi);

    printf("address of c = %p\n", pc);
    printf("address of i = %p\n", pi);

    printf("sizeof pc = sizeof pi = %ld = %ld\n", sizeof(pc), sizeof(pi));

    return 0;
}
