#include <stdio.h>
#include "common.h"

int main(void)
{
    int a = 0;
    unsigned int b = 0u;
    float c = 0;
    char *d = NULL;

    a = -100697;
    b = 100697u;
    c = 100697e-3;
    d = "string";

    printf("%c%c%c%c%c%c \n", 76, 't', '\163', 110, 'n', 104);

    printf("a (int) = %d \n", a);
    printf("a (unsigned int) = %u \n", a);     /* = (2^32 - |a|) */

    printf("b = %u = %o = %x \n", b, b, b);

    printf("c = %f = %e = %g \n", c, c, c);

    printf("%s \n", d);

    return 0;
}
