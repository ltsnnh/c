#include <stdio.h>
#include "common.h"

int main(void)
{
    int a = 8, b = 4, c = 6, max = 0;

    passing_argument_by_reference(&a, &b, &c, &max);

    printf("max passing argument by reference = %d\n", max);

    return 0;
}
