#include <stdio.h>
#include "common.h"

// int a = 4;      /* 11 */

int main(void)
{
    int a = 4;      /* 12 */

    printf("%d\n", ++a + ++a);

    return 0;
}
