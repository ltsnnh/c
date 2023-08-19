#include <stdio.h>
#include "common.h"

int main(void)
{
    char ch[10] = {}, ck[10] = {};

    /* 123 45XYZ123 */
    scanf("%[0123456789 ] %[^0123456789]", ch, ck);

    printf("%s \n", ch);    /* 123 45 */
    printf("%s \n", ck);    /* XYZ */

    return 0;
}
