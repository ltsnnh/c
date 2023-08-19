#include <stdio.h>
#include "common.h"

int x = 10;
int y = 11;

int main(void)
{
    int* const pconst = &x;

    /*pconst = &y;    // ERROR: assignment of read-only variable ‘pconst’*/

    printf("%d\n", *pconst);

    return 0;
}
