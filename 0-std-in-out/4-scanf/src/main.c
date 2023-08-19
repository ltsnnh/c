#include <stdio.h>
#include "common.h"

int main(void)
{
    int a = 0, b = 0;
    char ch[10] = {}, ck[10] = {};

    /* 35 13145XYZ584235 */
    // scanf("%d %[0123456789] %[^0123456789] %3d", &a, ch, ck, &b);
    /* above line seems work */
    // scanf("%d %[0123456789]%[^0123456789]%3d", &a, ch, ck, &b);
    /* above line seems work */
    // scanf("%d%[0123456789]%[^0123456789]%3d", &a, ch, ck, &b);
    /* above line works not like i understand */
    /* The above 3 lines should have given the same result */

    scanf("%d%[0123456789 ]%[^0123456789]%3d", &a, ch, ck, &b);
    /* above line works */

    printf("%d \n", a);     /* 35 */
    printf("%s \n", ch);    /*  13145 */
    printf("%s \n", ck);    /* XYZ */
    printf("%d \n", b);     /* 584 */

    return 0;
}
