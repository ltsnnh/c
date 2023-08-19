#include <stdio.h>
#include "common.h"

int main(void)
{
    int a = 0, i = 0;
    float b = 0;
    char ch[10] = {};

    i = scanf("%d %f %3s", &a, &b, ch);   /* 123.456a-123 */

    printf("%d \n", a);             /* 123 */
    printf("%f \n", b);             /* 0.456 */
    printf("%s \n", ch);            /* a-1 */

    printf("i = %d \n", i);         /* i = 3 = a number of read fields */

    return 0;
}

/**
 * int scanf(const char *str [,arguments]);
 *
 * return number of fields be read
 **/
