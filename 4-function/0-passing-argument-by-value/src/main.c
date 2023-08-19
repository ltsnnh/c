#include <stdio.h>
#include "common.h"

int main(void)
{
    int a = 1, b = 2, c = 3, max = 0;

    max = passing_argument_by_value(a, b, c);

    printf("max passing argument by value = %d\n", max);

    return 0;
}
