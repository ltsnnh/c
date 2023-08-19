#include <stdio.h>
#include "common.h"

int main(void)
{
    int *pa = NULL;
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int i = 0;

    printf("a = %p\n", a);
    printf("a + 1 = %p\n", a + 1);

    pa = (int*)a;

    for(i = 0; i < 6; i++)
    {
        printf("%d\t", *(pa + i));
    }

    putchar('\n');

    return 0;
}
