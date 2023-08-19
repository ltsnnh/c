#include <stdio.h>
#include "common.h"

int max_bc(int, int);
int max_abc(int, int, int, int (*)(int, int));

int main(void)
{
    int a = 5, b = 9, c = 3, max = 0;

    max = max_abc(a, b, c, max_bc);

    printf("max = %d\n", max);

    return 0;
}

int max_bc(int n, int p)
{
    return(n > p ? n : p);
}

int max_abc(int m, int n, int p, int (*pfunc)(int, int))
{
    int result = 0;

    result = m > pfunc(n, p) ? m : pfunc(n, p);

    return(result);
}
