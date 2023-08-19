#include <stdio.h>
#include "common.h"

int main(int n, char* a[])
{
    int i = 0;

    printf("n = %d\n", n);

    for (i = 0; i < n; i++)
    {
        puts(a[i]);
    }

    return 0;
}
