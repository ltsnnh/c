#include <stdio.h>
#include <float.h>
#include <limits.h>
#include "common.h"

int main(void)
{
    float a = 0, b = 0;

    a = 106.97;
    b = 10697e-2;

    printf("sizeof(float) = %ld \n", sizeof(float));                /* 4 */
    printf("sizeof(double) = %ld \n", sizeof(double));              /* 8 */
    printf("sizeof(long double) = %ld \n", sizeof(long double));    /* 16 */

    printf("float max = %g \n", (float)FLT_MAX);
    printf("float min = %g \n", (float)FLT_MIN);

    printf("double max = %g \n", (double)DBL_MAX);
    printf("double min = %g \n", (double)DBL_MIN);

    putchar('\n');

    printf("a = %e \n", a);
    printf("b = %f \n", b);

    return 0;
}
