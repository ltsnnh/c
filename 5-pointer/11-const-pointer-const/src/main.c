#include <stdio.h>
#include "common.h"

int x = 10;
int y = 11;

int main(void)
{
    const int* const pt = &x;

    /**pt = 12;   // ERROR: assignment of read-only location ‘*pt’*/
    /*pt = &y;    // ERROR: assignment of read-only variable ‘pt’*/

    printf("%d\n", *pt);

    return 0;
}
