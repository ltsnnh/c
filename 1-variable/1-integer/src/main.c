#include <stdio.h>
#include <limits.h>
#include "common.h"

int main(void)
{
    long a = 0l;
    int b = 0, c = 0;

    a = 10697l;     /* long */
    b = 0176;       /* int8 always >= 0 */
    c = 0xACBD;     /* int16 always >= 0 */

    printf("sizeof(short int) (byte) = %ld \n", sizeof(short));     /* 2 */
    printf("sizeof(int) (byte) = %ld \n", sizeof(int));             /* 4 */
    printf("sizeof(long int) (byte) = %ld \n", sizeof(long));       /* 8 */

    printf("short max = %hd \n", SHRT_MAX);
    printf("short min = %hd \n", SHRT_MIN);

    printf("int max = %d \n", INT_MAX);
    printf("int min = %d \n", INT_MIN);

    printf("long int max = %ld \n", (long)LONG_MAX);
    printf("long int min = %ld \n", (long)LONG_MIN);

    printf("unsigned short max = %hu \n", (unsigned short)USHRT_MAX);
    printf("unsigned int max = %u \n", (unsigned int)UINT_MAX);
    printf("unsigned long max = %lu \n", (unsigned long)ULONG_MAX);

    putchar('\n');

    printf("a = %ld \n", a);
    printf("b = %u = %o = %x \n", b, b, b);
    printf("c = %u = %o = %x \n", c, c, c);

    return 0;
}
