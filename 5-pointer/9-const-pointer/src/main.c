#include <stdio.h>
#include "common.h"

int x = 10;

int main(void)
{
    const int* px = NULL;   /* read-only */

    px = &x;

    /**px = 12;   // ERROR: assignment of read-only location ‘*px’*/

    printf("%d\n", *px);

    return 0;
}
